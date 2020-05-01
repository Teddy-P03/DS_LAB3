#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;

queue * 
create_queue (int capacity, int unit) ;

void
delete_queue (queue * que) ;

int 
enqueue (queue * que, void * elem) ;

int
dequeue (queue * que, void * elem) ;

int 
is_empty (queue * que) ;

int 
is_full (queue * que) ;

void
print_queue (queue * que, void (* print_element)(void * element)) ;

const int d[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};	//움직일 방향(남,동,북,서)

typedef struct{
	int y;
	int x;
} land;

int main(){
    int width, height, i, j;
    scanf("%d %d",&width, &height);
	
    int map[20][20] = {0,};				//맵 입력받기 //모든칸 0으로 초기화상태
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            scanf("%d",&(map[i][j]));
        }
    }
    	
	queue * que ;
	que = create_queue(width*height, sizeof(land)) ;
    int visited[20][20] = {0,};			//방문한 적이 있는 땅인가? //처음에 0으로 초기화
	int new_land[200] = {0}, nl=0;		//new_land의 각 인덱스에 섬의 크기 저장 //nl은 인덱스 표시
	int min=width*height, max=0, islands=0;

	i=0; j=0;
    while(i != height || j != width){//x축 y축이 둘 다 최대까지 가면
		if(map[i][j] == 1){					//섬에서의 첫걸음
			if(visited[i][j]!=1){			//섬에서의 첫걸음
				land init;
				init.y = i;
				init.x = j;
				enqueue(que,&init); visited[i][j] = 1;		//처음으로 밟은 땅을 queue에 집어넣기 + 방문표시
				new_land[nl]=1;								//섬의 크기 1로 초기화
				while(is_empty(que) == 0){
					land curr;
					dequeue(que,&curr);
					for(int k=0;k<4;k++){					
						land next;
						next.y = curr.y + d[k][0];
						next.x = curr.x + d[k][1];
						if(0<=next.x && next.x<width && 0<=next.y && next.y<height){
							if(map[next.y][next.x] == 1){
								if(visited[next.y][next.x] != 1){
									enqueue(que,&next); visited[next.y][next.x] = 1;
									new_land[nl]+=1;
								}
							}
						}
					}
				}
				nl+=1;
			}
		}
		if(j < width){
			j+=1;
		}
		else{
			j=0;
			i+=1;
		}
    } 

	for(int k = 0;k<200;k++){
		if(new_land[k] != 0){
			islands+=1;		//섬의 갯수
		}
	}
	for(int k = 0;k<islands;k++){
		if(max<new_land[k]) max = new_land[k];
		if(new_land[k]<min) min = new_land[k];
	}
   	printf("%d %d %d\n",islands, min, max);
	delete_queue(que) ;
    return 0;
}

queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	que->full = 0 ;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % que->capacity ;

	if (que->rear == que->front)
		que->full = 1 ;

	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % que->capacity ;	
	que->full = 0 ;

	return 0;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) && (que->full == 0) ;
}

int 
is_full (queue * que) 
{
	return que->full ;
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	if (que->front == que->rear && que->full == 0)
		return ;

	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}
