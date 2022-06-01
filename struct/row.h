#include <stdint-gcc.h>

#ifndef SQLITE_TABLE_H
#define SQLITE_PAGE_H
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
//get struct attribute size
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

typedef struct {
	uint32_t id;
	char username[COLUMN_USERNAME_SIZE];
	char email[COLUMN_EMAIL_SIZE];
} Row;

/**
 * Row Base Offset
 */
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
/**
 * serialize compact representation row data
 * @param source
 * @param destination
 */
void serialize_row(Row* source,void* destination);

/**
 * deserialize row data from compact representation
 * @param source
 * @param destination
 */
void deserialize_row(void* source,Row* destination);

#endif