#include "growing_arrays.h"

// returns the index of the item added  
int add_record(Record record) {
	if(table.nval == table.max){
		table.max *= GROW_SIZE;
		table.record = realloc(table.record, table.max * sizeof(Record));
		// doubles the allocated space by using realloc//
	}
	table.record[table.nval] = record;
	return table.nval++;
	//increments the record to the table//
}

// return 0 if there is no matching record
// return 1 if there is a matching record and deletes it and 
// moves records
int del_record(const char *name) {
	// we start to iterate through the list // 
	for(int i = 0; i < table.nval ; i++){
		// check if the current node matches the name, then deletes it//
		if(strcmp(table.record[i].name, name) == 0){
			memmove(table.record+1, table.record+i+1, (table.max-(i+1) * sizeof(Record)));
			return 1;
			// deletes the matching record//
		}
		table.nval--;
		//decrement the number of records//
	}
	return 0;
	// if theres no matching records//
}

// returns id of student record of the first matching record
int get_id(const char *name) {
    for(int i = 0; i < table.nval; i++){
	    // we proceed to iterate through the list again // 
	    if(strcmp(table.record[i].name, name) == 0){
		    //returns the id of the students record//
		    return table.record[i].id;
	    }
    }
    return 0;
}

// returns record with a valid index, 0 to max-1 
Record get_record(int index) {
	if(index < 0 || index >= table.nval){
		printf("Invalid Index detected");
		exit(EXIT_FAILURE);
	}
	return table.record[index];
	
}
/*
// Testing code. You can modify this and check your own test cases.
struct Table table; // If you are using another .c file to test your program comment this line as well.
int main() {
    table.nval = 0;
    table.max = INIT_SIZE;
    table.record = malloc(sizeof(Record) * table.max);

    // test add_record
    Record r1 = {"Alice", 1};
    Record r2 = {"Bob", 2};
    Record r3 = {"Charlie", 3};
    int i1 = add_record(r1);
    int i2 = add_record(r2);
    int i3 = add_record(r3);
    printf("added records at indices %d, %d, %d\n", i1, i2, i3);

    // test get_id and get_record
    int id = get_id("Bob");
    Record r = get_record(i1);
    printf("record at index %d: name=%s, id=%d\n", i1, r.name, r.id);
    printf("record with name 'Bob': id=%d\n", id);

    // test del_record
    int success = del_record("Bob");
    printf("deleted record with name 'Bob': %d\n", success);
    id = get_id("Bob");
    printf("record with name 'Bob': id=%d\n", id);

    free(table.record);
    return 0;
}
*/
/*
Output for the above testing code:

added records at indices 0, 1, 2
record at index 0: name=Alice, id=1
record with name 'Bob': id=2
deleted record with name 'Bob': 1
record with name 'Bob': id=0


*/
