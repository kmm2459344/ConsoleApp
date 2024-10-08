//======================================
//	リバーシ Vector2List
//======================================
#include "Vector2List.h"
#include <stdio.h>   // printf()
#include <stdlib.h>  // calloc(),free(),exit()
// 初期化
void InitializeVector2List(Vector2List* list, int size)
{
	list->array = (Vector2*)calloc(size, sizeof(Vector2));
	if (list->array == nullptr) {
		printf("calloc失敗\n");
		exit(1);
	}
	list->size = size;
	list->ptr = 0;
}
// 後始末
void FinalizeVector2List(Vector2List* list)
{
	free(list->array);
	list->size = 0;
	list->ptr = 0;
}
// リストに追加
void AddVector2List(Vector2List* list, Vector2 pos)
{
	if (list->ptr < list->size) {
		list->array[list->ptr++] = pos;
	}
}
// リストの要素数を得る
int GetCountVector2List(Vector2List* list)
{
	return list->ptr;
}
// リストの要素を得る
Vector2 GetVector2List(Vector2List* list, int idx)
{
	static Vector2 dummyPos = { -1,-1 };
	if (0 <= idx && idx < list->ptr) {
		return list->array[idx];
	}
	return  dummyPos;
}
// リストをクリアする
void ClearVector2List(Vector2List* list)
{
	list->ptr = 0;
}