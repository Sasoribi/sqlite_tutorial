#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_buffer.h"
#include "row.h"

typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
	PREPARE_SUCCESS,
	PREPARE_SYNTAX_ERROR,
	PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT
} StatementType;

typedef struct {
	StatementType type;
	Row row_to_insert;  // only used by insert statement
} Statement;

void execute_statement(Statement *statement);

/**
 * SQL compile -- transform SQL
 * @param input_buffer
 * @param statement
 * @return
 */
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement) {
	if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		//sscanf()->read input from str
		int args_assigned = sscanf(
				input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
				statement->row_to_insert.username, statement->row_to_insert.email);
		if (args_assigned < 3) {
			return PREPARE_SYNTAX_ERROR;
		}
		return PREPARE_SUCCESS;
	}
	if (strncmp(input_buffer->buffer, "select", 6) == 0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}
	return PREPARE_UNRECOGNIZED_STATEMENT;
}

void print_prompt() { printf("db > "); }

/**
 * meta-command -- Non-SQL command
 * @param input_buffer
 * @return
 */
MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
	if (strcmp(input_buffer->buffer, ".exit") == 0) {
		exit(EXIT_SUCCESS);
	} else {
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(int argc, char *argv[]) {
	InputBuffer *input_buffer = new_input_buffer();
	while (true) {
		print_prompt();
		//read InputData in input_buffer
		read_input(input_buffer);

		if (input_buffer->buffer[0] == '.') {
			//meta-command resolve
			switch (do_meta_command(input_buffer)) {
				case META_COMMAND_SUCCESS:
					continue;
				case META_COMMAND_UNRECOGNIZED_COMMAND:
					printf("Unrecognized command %s .\n", input_buffer->buffer);
					continue;
			}
		}
		Statement statement;
		//statement-representation
		switch (prepare_statement(input_buffer, &statement)) {
			case PREPARE_SUCCESS:
				break;
			case PREPARE_SYNTAX_ERROR:
				printf("Syntax error!");
				break;
			case PREPARE_UNRECOGNIZED_STATEMENT:
				printf("Unrecognized keyword at start of %s .\n", input_buffer->buffer);
				continue;
		}

		execute_statement(&statement);
		printf("Executed.\n");
	}
}

void execute_statement(Statement *statement) {
	switch (statement->type) {
		case STATEMENT_INSERT:
			printf("This is where we would do an insertion!");
			break;
		case STATEMENT_SELECT:
			printf("This is where we would do a selection!");
			break;
	}
}
