fourDrection 4;

typedef struct{
    int x ;
    int y ;
} pos ;

/*typedef struct{
    int bst ; // biggest
    int sst ; // smallest
    int cnt ;  // count Land number
} task ;*/

int dir[fourDirection][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}} ;

int
main(){

    int width ;
    int height ;
    scanf("%d %d\n", &width, &height) ;
    
    int map[width][height] ;
    int visited[width][height] ;

    for (int w=0; w<width; w++){
        for (int h=0; h<height; h++){
            scanf("%d", &map[w][h]) ;
            visited[w][h] = 0 ;     //한번에 전체 초기화 할 필요없이 어차피 사용해야할 반복문을 이용해 초기화하는 것이 나은 듯하다
                                    //용량도 적다
        }
    }

/*for (int w=0; w<width; w++){
        for (int h=0; h<height; h++){
            printf("%d ", map[w][h]);
        }
        printf("\n");
    }*/

    queue * llist ;
    llist = create_queue(width*height, sizeof(pos)) ;
    
    pos land ;
    int biggest = 0 ;
    int smallest = width*height ;
    int countL = 0 ;
    int area ;
    int checkDone = 1 ;

    do{
        checkDone = 1 ;
        for (int w=0; w<width; w++){        //하나의 섬의 조사한 다음 다른 섬을 찾으러 갈때, 매번 처음부터 시작하는건 비효율 적이다.
            for (int h=0; h<height; h++){
                if (map[w][h] == 1 && visited[w][h] != 1){
                    visited[w][h] = 1 ;
                    land.x = w ;
                    land.y = h ;
                    enqueue(llist, &land) ;
                    break ;
                }
            }
            if (!is_empty(llist)){
                checkDone = 0 ;
                countL += 1 ;           //내 방법보다 효율적이다.
                area = 1 ;
                printf("Track1\n");
                break ;
            }                           //아래의 while문과 if문을 여기 if문에 넣으면 되지 않을까?
                                        // + do while 문이 종료될 조건도 변경
                                        //그러면 섬찾기 매번 처음부터 시작하는 비효율은 사라짐
        }

        while (!is_empty(llist)){
            pos curr ;
            dequeue(llist, &curr) ;
            for (int i=0; i<fourDirection; i++){
                pos next ;
                next.x = curr.x + dir[i][0] ;
                next.y = curr.y + dir[i][1] ;
                int n_x = next.x ;
                int n_y = next.y ;
                if (!(n_x < 0 || n_y < 0)){
                    if (map[n_x][n_y] == 1 && visited[n_x][n_y] != 1){
                        visited[n_x][n_y] = 1 ;
                        enqueue(llist, &next) ;
                        area += 1 ;
                        printf("Track2\n");
                    }
                }
            }
            printf("Track3\n");
        }

        if (checkDone != 1){        //area가 도출될 때마다 비교를 통해 max min을 구하는 게, 내 방법보다 용량이 적게 든다.
            if (biggest <= area){
                biggest = area ;
            }
            if (area <= smallest){
                smallest = area ;
            }
        }
        printf("Track4\n");
    } while (checkDone != 1) ;

    printf("%d %d %d\n", countL, smallest, biggest);
    
    delete_queue(llist) ;
    return 0 ;
}

