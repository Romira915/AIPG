#include <stdlib.h>
#include "List.h"

// リストの初期化
void initList(List* list) {
	list->top = NULL;
	list->bottom = NULL;
}

// セルの確保
Cell* createCell() {
	return (Cell*)malloc(sizeof(Cell));
}

// セルの開放
void disposeCell(Cell* c) {
	free(c);
}

// リストの先頭にデータを追加
void addTop(List* list, Cell* c) {
	c->prev = NULL;
	c->next = list->top;
	if (list->top == NULL) {
		list->bottom = c;
	}
	else {
		list->top->prev = c;
	}
	list->top = c;
}

// リストの末尾にデータを追加
void addBottom(List* list, Cell* c) {
	c->prev = list->bottom;
	c->next = NULL;
	if (list->bottom == NULL) {
		list->top = c;
	}
	else {
		list->bottom->next = c;
	}
	list->bottom = c;
}

// ソート済みのリストにデータを追加
void addSorted(List* list, Cell* c) {
	if (list->top == NULL || c->value <= list->top->value) {
		addTop(list, c);
	}
	else if (list->bottom->value < c->value) {
		addBottom(list, c);
	}
	else if (c->value - list->top->value <= list->bottom->value - c->value) {
		Cell* p;
		for (p = list->top; p->value < c->value; p = p->next);
		p->prev->next = c;
		c->prev = p->prev;
		c->next = p;
		p->prev = c;
	}
	else {
		Cell* p;
		for (p = list->bottom; c->value <= p->value; p = p->prev);
		p->next->prev = c;
		c->next = p->next;
		c->prev = p;
		p->next = c;
	}
}

// リストの先頭からデータを取り出し
Cell* takeTop(List* list) {
	if (list->top == NULL) {
		return NULL;
	}
	else {
		Cell* c = list->top;
		list->top = c->next;
		if (c->next == NULL) {
			list->bottom = NULL;
		}
		else {
			c->next->prev = NULL;
		}
		return c;
	}
}

// リストの末尾からデータを取り出し
Cell* takeBottom(List* list) {
	if (list->bottom == NULL) {
		return NULL;
	}
	else {
		Cell* c = list->bottom;
		list->bottom = c->prev;
		if (c->prev == NULL) {
			list->top = NULL;
		}
		else {
			c->prev->next = NULL;
		}
		return c;
	}
}

