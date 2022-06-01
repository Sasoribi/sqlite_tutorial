#include "row.h"
#include "string.h"

void serialize_row(Row *source, void *destination) {
	//copy row.id -> dest.id
	memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
	memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
	memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}


void deserialize_row(void *source, Row *destination) {
	memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
	memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_OFFSET);
	memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}
