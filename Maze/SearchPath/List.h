typedef struct cell {
	int x, y, value, id;
	struct cell* prev;
	struct cell* next;
} Cell;

typedef struct {
	Cell *top;
	Cell *bottom;
} List;

// リストの初期化
void initList(List* list);

// セルの確保
Cell* createCell();

// セルの開放
void disposeCell(Cell* c);

// リストの先頭にデータを追加
void addTop(List* list, Cell* c);

// リストの末尾にデータを追加
void addBottom(List* list, Cell* c);

// ソート済みのリストにデータを追加
void addSorted(List* list, Cell* c);

// リストの先頭からデータを取り出し
Cell* takeTop(List* list);

// リストの末尾からデータを取り出し
Cell* takeBottom(List* list);