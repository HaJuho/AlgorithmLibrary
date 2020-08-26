/*****************************************************************************
*****************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <string>
#include <algorithm>

using namespace std;

/*****************************************************************************
*****************************************************************************/
const int DEF_DATA_VAL = -987654321;
const int DEF_BUCKET_SIZE = 16;
const int LOAD_FACTOR = 10;
const int MAX_LOAD = 20;

class HashNode {
	int key;
	int val;
	HashNode* next;
	HashNode(int _key, int _val, HashNode* _next) : key(_key), val(_val), next(_next) {}
	friend class HashBucket;
	friend class HashTable;
};

class HashBucket {
	int count;
	HashNode* head;
	HashBucket() : count(0), head(NULL) {}
	~HashBucket()
	{
		HashNode* node = head;
		while (node != NULL) {
			HashNode* temp = node;
			node = node->next;
			delete temp;
		}
	}

	HashNode* findNode(int key) const;
	HashNode* removeNode(int key);
	bool insertNode(int key, int val);
	bool insertNode(HashNode* node);
	friend class HashTable;
};

class HashTable {
	int bsize;
	int count;
	HashBucket* buckets;
	HashTable() : bsize(DEF_BUCKET_SIZE), buckets(new HashBucket[DEF_BUCKET_SIZE]) {}
	~HashTable() { delete[] buckets; }

	int hash(int key) const;
	void rehash();
	HashBucket* findBucket(int key) const;
public:
	bool contains(int key) const;
	bool insert(int key, int val);
	int get(int key) const;
	int remove(int key);
};

HashNode* HashBucket::findNode(int key) const
{
	HashNode* node = head;
	while (node != NULL && node->key != key)
		node = node->next;
	return node;
}

HashNode* HashBucket::removeNode(int key)
{
	if (head == NULL)
		return NULL;
	HashNode* node = head;
	if (node->key == key) {
		head = node->next;
		node->next = NULL;
		count--;
		return node;
	}
	while (node->next != NULL) {
		HashNode* temp = node->next;
		if (temp->key == key) {
			node->next = temp->next;
			temp->next = NULL;
			count--;
			return temp;
		}
		node = temp;
	}
	return NULL;
}

bool HashBucket::insertNode(int key, int val)
{
	HashNode* node = findNode(key);
	if (node != NULL) {
		node->val = val;
		return false;
	}
	head = new HashNode(key, val, head);
	count++;
	return true;
}

bool HashBucket::insertNode(HashNode* node)
{
	node->next = head;
	head = node;
	count++;
	return true;
}

int HashTable::hash(int key) const
{
	return key;
}

void HashTable::rehash()
{
	int nbsize = bsize * 2;
	HashBucket* nbuckets = new HashBucket[nbsize];
	for (int i = 0; i < bsize; ++i) {
		HashBucket* bkt = &buckets[i];
		while (bkt->head != NULL) {
			HashNode* node = bkt->removeNode(bkt->head->key);
			nbuckets[hash(node->key) % nbsize].insertNode(node);
		}
	}
	delete[] buckets;
	buckets = nbuckets;
	bsize = nbsize;
}

HashBucket* HashTable::findBucket(int key) const
{
	return &buckets[hash(key) % bsize];
}

bool HashTable::contains(int key) const
{
	return findBucket(key)->findNode(key) != NULL;
}

bool HashTable::insert(int key, int data)
{
	HashBucket* bucket = findBucket(key);
	if (bucket->insertNode(key, data)) {
		count++;
		if (bucket->count > MAX_LOAD || count > LOAD_FACTOR * bsize)
			rehash();
		return true;
	}
	return false;
}

int HashTable::get(int key) const
{
	HashNode* node = findBucket(key)->findNode(key);
	return node == NULL ? DEF_DATA_VAL : node->val;
}

int HashTable::remove(int key)
{
	HashNode* node = findBucket(key)->removeNode(key);
	if (node == NULL) {
		return DEF_DATA_VAL;
	}
	count--;
	int val = node->val;
	delete node;
	return val;
}

/*****************************************************************************
*****************************************************************************/
int main(int argc, char* argv[])
{
	return 0;
}
