/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {//Node를 struct로 선언(지정)
	int key; //정수형 변수 key 선언
	struct Node* llink; //Node에 대한 포인터 llink 선언
	struct Node* rlink;//Node에 대한 포인터 rlink 선언
} listNode; //구조체 별칭 listNode

/* 함수 리스트 */
int initialize(listNode** h); //headNode에 메모리를 할당하여 초기화하는 함수 선언 (이중포인터를 매개변수로 함)
//이중포인터를 매개변수로 할 경우 포인터 h의 값을 변경할 수 있음
//싱글포인터를 매개변수로 할 경우 값을 변경할 수 없음.
//해당 코드의 linitialize는 포인터의 값을 변경하기 위해 이중포인터를 매개변수로 받도록 구현함.
int freeList(listNode* h); //할당된 메모리를 해제하는 함수 선언
int insertLast(listNode* h, int key); //list의 끝 부분에 key에 대한 노드를 추가하는 함수 선언
int deleteLast(listNode* h); //list의 마지막 노드를 삭제하는 함수 선언
int insertFirst(listNode* h, int key); //list의 첫 부분에 key에 대한 노드를 추가하는 함수 선언
int deleteFirst(listNode* h); //list의 첫 노드를 삭제하는 함수 선언
int invertList(listNode* h); //list의 link를 역순으로 재배치하는 함수 선언

int insertNode(listNode* h, int key); //list에 key에 대한 노드를 추가하는 함수 선언
int deleteNode(listNode* h, int key); //list의 노드 하나를 삭제하는 함수 선언

void printList(listNode* h); //list를 출력하는 함수 선언




int main()
{
	char command; //문자형 변수 command 선언
	int key;//정수형변수 key선언
	listNode* headnode=NULL;  //listNode 에 대한 포인터 headnode  초기화

	do{
		printf("[----- [Gahyun.Kim] [2020045070] -----]");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //메뉴 선택 입력

		switch(command) {//command 값에 따른 switch 조건문
		case 'z': case 'Z': //z를 입력받았을 경우 (대소문자 모두 가능)
			initialize(&headnode); //headnode의 주소를 매개변수로 하는 initialize 함수를 호출하여 메모리 할당 
			break;
		case 'p': case 'P': //p를 입력받았을 경우 (대소문자 모두 가능)
			printList(headnode); //list 출력
			break;
		case 'i': case 'I': //i를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);//key 입력 
			insertNode(headnode, key);//key에 대한 노드 추가
			break;
		case 'd': case 'D': //d를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);//key 입력
			deleteNode(headnode, key); //key에 대한 노드 하나 삭제
			break;
		case 'n': case 'N': //n를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);//key 입력
			insertLast(headnode, key); //list의 마지막에 노드 하나 추가
			break;
		case 'e': case 'E'://e를 입력받았을 경우 (대소문자 모두 가능)
			deleteLast(headnode); //list의 마지막 노드 삭제
			break;
		case 'f': case 'F': //f를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key); //key 입력
			insertFirst(headnode, key); //list의 첫 부분에 노드 하나 추가
			break;
		case 't': case 'T': //t를 입력받았을 경우 (대소문자 모두 가능)
			deleteFirst(headnode); //list의 첫 노드 삭제
			break;
		case 'r': case 'R': //r를 입력받았을 경우 (대소문자 모두 가능)
			invertList(headnode); //lsit 재배열
			break;
		case 'q': case 'Q': //q를 입력받았을 경우 (대소문자 모두 가능)
			freeList(headnode); //할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q를 입력받기 전까지 반복

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //포인터 h가 NULL이 아닐때 /headNode가 NULL이 아닐 때 /즉 node가 존재할 때
		freeList(*h); //할당된 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); //포인터 h에 listNode의 크기만큼의 메모리 할당
	(*h)->rlink = *h; //포인터 h의 rlink에 포인터 h 저장
	(*h)->llink = *h; //포인터 h의 llink에 포인터 h 저장
	(*h)->key = -9999; //포인터 h의 key를 -9999로 초기화
	//위의 초기화를 통해 원형 리스트 구현
	return 1;
}

int freeList(listNode* h){ // h와 연결된 listNode 메모리 해제

	if(h->rlink == h) //만약 h의 rlink가 h일 경우
	{
		free(h); //h에 할당된 메모리 해제
		return 1;
	}

	listNode* p = h->rlink; //listNode 포인터 p선언 후 h의 rlink를 저장

	listNode* prev = NULL; //listNode 포인터 prev 선언 후 초기화
	while(p != NULL && p != h) { //p가 NULL이 아니고 h도 아닐 동안
		prev = p; //prev 에 p 저장
		p = p->rlink; //p에 p의 rlink 저장
		free(prev); //prev에 할당된 메모리 해제
	}
	free(h); //h에 할당된 메모리 해제
	return 0;
}



void printList(listNode* h) { 
	int i = 0; //정수형 변수 i 선언 후 0으로 초기화
	listNode* p; //listNode 포인터 p선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL일 경우, node가 존재하지 않을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p에 h의 rlink를 저장

	while(p != NULL && p != h) { //p가 NULL이 아니고 p가 h도 아닐 동안
		printf("[ [%d]=%d ] ", i, p->key); //p의 key를 통해 저장된 값 출력
		p = p->rlink; //p에 p의 rlink 저장
		i++; //i++
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0; //i 초기화
	p = h->rlink; //p에 h의 rlink 저장
	while(p != NULL && p != h) { //p가 NULL이 아니고 h도 아닐 동안
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); 
		//p의 key , p의 llink, p의 rlink 출력
		p = p->rlink; //p에 p의 rlink 저장
		i++; 
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) //h가 NULL이면, 
	return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 listNode의 포인터 node에 저장
	node->key = key; //node의 key 부분에 입력받은 key 저장
	node->rlink = NULL; //node의 rlink NULL로 초기화
	node->llink = NULL; //node의 llink NULL로 초기화

	if (h->rlink == h) //h의 rlink가 h일 경우
	/* 첫 노드로 삽입 */
	{
		h->rlink = node; //h의 rlink에 node 저장
		h->llink = node; //h의 llink에 node 저장
		node->rlink = h; //node의 rlink에 h 저장
		node->llink = h; //node의 llink에 h 저장
	} else {
		h->llink->rlink = node; //h의 llink의 rlink에 node 저장
		node->llink = h->llink; //node의 llink에 h의 llink 저장
		h->llink = node; //h의 llink에 node 저장
		node->rlink = h; //node의 rlink에 h 저장
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //h의 llink가 h이거나 h가 NULL일 경우 node가 존재하지 않을 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //listNode의 포인터 nodetoremove에 h의 llink 저장

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의 llink의 rlink에 h 저장
	h->llink = nodetoremove->llink; //h의 llink에 nodetoremove의 llink 저장

	free(nodetoremove); //nodetoremove에 할당된 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	//listNode의 포인터 node에 listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key 부분에 입력받은 key 저장
	node->rlink = NULL; //node의 rlink NULL로 초기화
	node->llink = NULL; //node의 llink NULL로 초기화


	node->rlink = h->rlink; //node의 rlink에 h의 rlink 저장
	h->rlink->llink = node; //h의 rlink의 llink에 node 저장
	node->llink = h; //node의 llink에 h 저장
	h->rlink = node; //h의 rlink에 node 저장


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //h가 NULL이거나 h의 rlink가 h일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //listNode의 포인터 nodetoremove에 h의 rlink 저장

	/* link 정리 */
	nodetoremove->rlink->llink = h; //nodetoremove의 rlink의 llink에 h 저장
	h->rlink = nodetoremove->rlink; //h의 rlink에 nodetoremove의 rlink 저장

	free(nodetoremove); //nodetoremove에 할당된 메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //h의 rlink가 h이거나 h가 NULL일 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; //listNode의 포인터 n에 h의 rlink 저장 
	listNode *trail = h; //listNode의 포인터 trail에 h 저장
	listNode *middle = h; //listNode의 포인터 middle에 h 저장

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; //h의 llink에 h의 rlink 저장

	while(n != NULL && n != h){ //n이 NULL이 아니고 h도 아닐동안
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->rlink; //n에 n의 rlink 저장
		middle->rlink = trail; //middle의 rlink에 trail 저장
		middle->llink = n; //middle의 llink에 n 저장
	}

	h->rlink = middle; //h의 rlink에 middle 저장

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //h가 NULL일 경우 노드가 존재하지 않을 경우

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 포인터 node에 listNode의 크기만큼 메모리할당
	node->key = key; //node의 key부분에 입력받은 key 저장
	node->llink = node->rlink = NULL; //node의 llink에 node의 rlink 저장,NULL로 초기화

	if (h->rlink == h) //h의 rlink가 h일 경우 
	{
		insertFirst(h, key); //첫번째 노드에 삽입
		return 1;
	}

	listNode* n = h->rlink; //listNode의 n에 h의 rlink 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { //n이 NULL이 아니고 h도 아닐 경우
		if(n->key >= key) { //n의 key가 입력받은 key 보다 클 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 h의 rlink라면
				insertFirst(h, key); //첫번째노드에 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node의 rlink에 n 저장
				node->llink = n->llink; //node의 llink에 n의 llink 저장
				n->llink->rlink = node; //n의 llink의 rlink에 node 저장
				n->llink = node; //n의 llink에 node 저장
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //마지막 노드에 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)  //h의 rlink가 h이거나 h가 NULL일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //listNode의 포인터 n에 h의 rlink 저장

	while(n != NULL && n != h) { //n이 NULL이 아니고 h도 아닐 동안 (노드가 존재할 동안)
		if(n->key == key) { //n의key가 입력받은 key와 같을 때
			if(n == h->rlink) { /* 첫 번째 노드 인경우 */
				deleteFirst(h); //첫번째노드삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막노드삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 llink의 rlink에 n의 rlink 저장
				n->rlink->llink = n->llink; //n의 rlink의 llink에 n의 llink 저장
				free(n); //n에 할당된 메모리 해제
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


