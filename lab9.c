#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
};

// Node for linked list in HashType
struct ListNode {
    struct RecordType data;
    struct ListNode* next;
};

// HashType structure
struct HashType {
    struct ListNode** array;
    int size;
};

// Create a new ListNode
struct ListNode* newListNode(struct RecordType data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Compute the hash function
int hash(int x, int hashSize) {
    return x % hashSize;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType data) {
    int index = hash(data.id, hashTable->size);
    struct ListNode* newNode = newListNode(data);
    newNode->next = hashTable->array[index];
    hashTable->array[index] = newNode;
}

// Function to display records in the hash table
void displayRecordsInHash(struct HashType *hashTable) {
    printf("\nHash Table:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct ListNode* node = hashTable->array[i];
        if (node != NULL) {
            printf("Index %d -> ", i);
            while (node != NULL) {
                printf("%d %c %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}
int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;
    const int hashSz = 23; // Define the size of the hash table

    // Parse data from the file
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
	//your hash implementation 
    // Initialize hash table
    struct HashType hashTable;
    hashTable.size = hashSz;
    hashTable.array = (struct ListNode**)malloc(hashSz * sizeof(struct ListNode*));
    for (int i = 0; i < hashSz; ++i) {
        hashTable.array[i] = NULL;
    }
    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(&hashTable, pRecords[i]);
    }
    // Display records in the hash table
    displayRecordsInHash(&hashTable);
    return 0;
}