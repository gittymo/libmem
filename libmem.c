/*	libmem.c
		Handle dynamic memory allocation a bit more sensibly.
		(C)2021 Morgan Evans */

#include "libmem.h"

void _MEMMAN_INIT()
{
	_MEMMAN_ = (MEMMAN *) malloc(sizeof(MEMMAN));
	if (_MEMMAN_ != NULL) {
		_MEMMAN_->record_count = 0;
		_MEMMAN_->current_record_capacity = _MEMMAN_RECORD_CAPACITY_INC;
		_MEMMAN_->record_ids = (void **) malloc(sizeof(void *) * _MEMMAN_->current_record_capacity);
		if (_MEMMAN_->record_ids != NULL) {
			_MEMMAN_->records = (_MEMMAN_RECORD **) malloc(sizeof(_MEMMAN_RECORD *) * _MEMMAN_->current_record_capacity);
		}
		if (_MEMMAN_->records == NULL || _MEMMAN_->record_ids == NULL) {
			if (_MEMMAN_->record_ids != NULL) {
				free(_MEMMAN_->record_ids);
				_MEMMAN_->record_ids = NULL;
			}
			if (_MEMMAN_->records != NULL) {
				free(_MEMMAN_->records);
				_MEMMAN_->records = NULL;
			}
			_MEMMAN_->record_count = 0;
			_MEMMAN_->current_record_capacity = 0;
			free(_MEMMAN_);
			_MEMMAN_ = NULL;
		}
		if (_MEMMAN_ != NULL) {
			atexit(&_MEMMAN_EXIT);
		}
	}
}

void * MEMMAN_ALLOC(int32_t size_in_bytes)
{
	void * m = NULL;
	if (_MEMMAN_ == NULL) _MEMMAN_INIT();
	if (_MEMMAN_ != NULL && _MEMMAN_->record_count < _MEMMAN_->current_record_capacity && size_in_bytes > 0) {
		m = (void *) malloc(sizeof(int8_t) * size_in_bytes);
		if (m != NULL) {
			_MEMMAN_RECORD * mmr = (_MEMMAN_RECORD *) malloc(sizeof(_MEMMAN_RECORD));
			if (mmr != NULL) {
				mmr->_manager = _MEMMAN_;
				mmr->data_length = size_in_bytes;
				_MEMMAN_->records[_MEMMAN_->record_count] = mmr;
				_MEMMAN_->record_ids[_MEMMAN_->record_count] = m;
				_MEMMAN_->record_count++;
				if (_MEMMAN_->record_count == _MEMMAN_->current_record_capacity) {
					_MEMMAN_->current_record_capacity += _MEMMAN_RECORD_CAPACITY_INC;
					void ** newRecIdsPtr = (void **) realloc(_MEMMAN_->record_ids, sizeof(void *) * _MEMMAN_->current_record_capacity);
					if (newRecIdsPtr != NULL) {
						_MEMMAN_RECORD ** newRecsPtr = 
							(_MEMMAN_RECORD **) realloc(_MEMMAN_->records, sizeof(_MEMMAN_RECORD *) * _MEMMAN_->current_record_capacity);
						if (newRecsPtr != NULL) {
							_MEMMAN_->record_ids = newRecIdsPtr;
							_MEMMAN_->records = newRecsPtr;
						} else {
							_MEMMAN_->current_record_capacity -= _MEMMAN_RECORD_CAPACITY_INC;
						}
					}
				}
			}
		}
	}
	return m;
}

void * MEMMAN_REALLOC(void * data_ptr, int32_t new_size_in_bytes)
{
	void * m = NULL;
	if (_MEMMAN_ == NULL) _MEMMAN_INIT();
	if (_MEMMAN_ != NULL && data_ptr != NULL && new_size_in_bytes > 0) {
		for (int32_t i = 0; i < _MEMMAN_->record_count; i++) {
			if (_MEMMAN_->record_ids[i] == data_ptr && _MEMMAN_->records[i]->_manager == _MEMMAN_) {
				m = (void *) realloc(data_ptr, sizeof(int8_t) * new_size_in_bytes);
				if (m != NULL) {
					_MEMMAN_->record_ids[i] = m;
					_MEMMAN_->records[i]->data_length = new_size_in_bytes; 
				} else m = data_ptr;
				break;
			}
		}
	}
	return m;
}

int32_t MEMMAN_FREE(void * data_ptr)
{
	int32_t memory_freed = 0;
	if (_MEMMAN_ == NULL) _MEMMAN_INIT();
	if (_MEMMAN_ != NULL && data_ptr != NULL) {
		for (int32_t i = 0; i < _MEMMAN_->record_count; i++) {
			if (_MEMMAN_->record_ids[i] == data_ptr && _MEMMAN_->records[i]->_manager == _MEMMAN_) {
				memory_freed = _MEMMAN_->records[i]->data_length;
				free(data_ptr);
				for (int32_t j = i; j < _MEMMAN_->record_count - 1; j++) {
					_MEMMAN_->records[j] = _MEMMAN_->records[j + 1];
					_MEMMAN_->record_ids[j] = _MEMMAN_->record_ids[j + 1];
				}
				_MEMMAN_->record_count--;
				break;
			}
		}
	}
	return memory_freed;
}

void _MEMMAN_EXIT()
{
	if (_MEMMAN_ != NULL) {
		for (int32_t i = 0; i < _MEMMAN_->record_count; i++) {
			free(_MEMMAN_->record_ids[i]);
			_MEMMAN_->records[i]->data_length = 0;
			_MEMMAN_->records[i]->_manager = NULL;
			free(_MEMMAN_->records[i]);
			_MEMMAN_->record_ids[i] = NULL;
		}
		free(_MEMMAN_->records);
		free(_MEMMAN_->record_ids);
		_MEMMAN_->record_count = _MEMMAN_->current_record_capacity = 0;
		_MEMMAN_->record_ids = NULL;
		_MEMMAN_->records = NULL;
		free(_MEMMAN_);
		_MEMMAN_ = NULL;
	}
}