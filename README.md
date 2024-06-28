## Example using 
```cpp
int can_comm_init(can_communicator_t* const self, CAN_HandleTypeDef * const hcan)
{
	M_Assert_BreakSaveCheck(self == NULL, M_EMPTY,
			return CTYPE_FALSE,
					"null");

	M_Assert_BreakSaveCheck(CallbackManager_init(&self->RX.callb) != 0, M_EMPTY,
			return CTYPE_FALSE,
					"callback manager not init");

	CallbackManager_subscribe(&self->RX.callb, 0x00, Ping, NULL);


	M_Assert_BreakSaveCheck(poolContainer_init(&self->TX.pool, 16, 256), M_EMPTY,
			return CTYPE_FALSE,
					"pool container not init");

	self->BID = 0x01;
	self->TX.remaining_bytes 	= 0;
	self->TX.ptr_align 			= 0;
	self->TX.chunks 			= 0;
	self->TX.chunk_number 		= 0;

	self->RX.msg_flags = 0;

	// initialization periphery
	M_Assert_BreakSaveCheck(bxCan_init(&self->can_handle, hcan, CAN_Filter_init) != 0, M_EMPTY,
			return CTYPE_FALSE,
					"can handler not init");
	return CTYPE_TRUE;
}

```
