#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_RESERVED_PEOPLE 10

// 방 안에 존재하는 칸을 구조체로 정의
struct sub_room{
    char person_name[30];
    struct sub_room* next; // 칸은 링크드 리스트 형태로 구현된다.
};

// 방이 어떤 타입인지 구조체로 정의
struct type{
    int price;
    int max_people;
};

struct room{
    int room_number;
    struct sub_room* sub_r;
    struct type* room_type;
};

int money = 1000; // 현재 상태의 돈

// 건물을 배열로 정의
// 인덱스로 층별, 칸별 접근이 용이
struct room building[100][100];

// 현재 건물의 너비
int current_building_width = 3;

// 현재 건물의 최고 층수
int current_building_height = 1;

struct type t_array[3] = {
    {100, 4},
    {200, 5},
    {300, 6}
};

// 예약자 명단을 정의
// 명단 배열 순서대로 방에 배정
char reserved_people[MAXIMUM_RESERVED_PEOPLE][30] = {""};;

void re_booked_list();

// ==================================================
void print_building(void)
{
    // 건물의 모습을 보여줌
    int i,j;
    int curr_room_number;
    
    printf("\n\n=======현재 빌딩의 상태=======\n\n");
    
    for(i=(current_building_height - 1); i>-1; i--)
    {
        for(j=0; j<current_building_width; j++)
        {
            printf("ㅡㅡㅡ");
        }
        
        printf("\n");
        
        for(j=0; j<(current_building_width); j++)
        {
            curr_room_number = building[i][j].room_number;
            if(curr_room_number > 100){
                
                printf("| ");
                printf("%d ", curr_room_number);
            }
        }
        printf("| \n");
    }
    
    for(j=0; j<current_building_width; j++)
    {
        printf("ㅡㅡㅡ");
    }
    printf("\n\n");
    printf("=============================\n");
    
    return;
}

void print_room(int x, int y)
{
    // 한 방에 대한 정보를 보여줌
    struct sub_room* curr;
    struct room this_room= building[x-1][y-1];
    printf("\n\n=======이 방의 정보=======\n");
    
    printf("- 선택된 방 : %d호\n", x*100 + y);
    
    if(this_room.room_type == NULL)
    {
        printf("아직 사용가능한 방이 아닙니다.");
    }else{
        printf("- 가격 : %d만원 \n", this_room.room_type->price);
        printf("- 최대 인원수 : %d명 \n", this_room.room_type->max_people);
        printf("- 거주자 목록 : ");
        curr = this_room.sub_r;
        
        while(1)
        {
            if(curr == NULL)
            {
                break;
            }
            
            printf("%s  ", curr->person_name);
            curr = curr->next;
        }
    }
    printf("\n");
    printf("=====================\n");
    return;
}

void print_sub_room(int x, int y, char* name)
{
    // 입력된 사람이 방에 존재하는지 확인
    struct sub_room* curr;
    struct room this_room= building[x-1][y-1];
    
    curr = this_room.sub_r;
    
    while(1)
    {
        if(curr == NULL)
        {
            break;
        }
        
        if(strcmp(curr->person_name, name)==0)
        {
            printf("%s 가 %d 방에 있습니다. \n", name, x*100+y);
            return;
        }
        curr = curr->next;
    }
    
    printf("거주자를 찾을 수 없습니다. \n");
    return;
}

void print_manager(void)
{
    // 출력에 대한 함수들을 관리하는 매니저 함수
    int selected, available_rooms=0, entire_people=0;
    int i,j,k;
    int x,y;
    char name[30];
    struct sub_room* curr_sub_r;
    
    while(1)
    {
        printf("[1]-최고 층 수 출력           [2]-현재 너비 출력 \n");
        printf("[3]-전체 방 수 출력           [4]-전체 거주자 수 출력 \n");
        printf("[5]-전체 건물 상태 출력       [6]-방 내부 상태 출력 \n");
        printf("[7]-칸 내부 상태 출력         [8]-현재 돈 출력 \n");
        printf("하위 메뉴를 선택하십시오 : (종료 : -1)\n");
        scanf("%d", &selected);
        
        if (selected == 1)
        {
            printf(">>현재 최고층은 %d 층 입니다.\n",current_building_height);
        }
        else if (selected == 2)
        {
            printf(">>현재 건물의 너비는 %d입니다.\n",current_building_width);
        }
        else if (selected == 3)
        {
            for(i=0; i<current_building_height; i++)
            {
                for(j=0; j<current_building_width; j++)
                {
                    if(building[i][j].room_type != NULL)
                        // 타입이 지정된 방만 사용 가능한 방으로 인식한다.
                        available_rooms++;
                }
            }
            
            printf(">>현재 방은 %d개가 있습니다. \n", current_building_height*current_building_width);
            printf(">>그 중 현재 사용 가능한 방은 %d 개 입니다.\n", available_rooms);
        }
        else if (selected == 4)
        {
            for(i=0; i<current_building_height; i++)
            {
                for(j=0; j<current_building_width; j++)
                {
                    
                    curr_sub_r = building[i][j].sub_r;
                    while(1){
                        if(curr_sub_r == NULL)
                            break;
                        else{
                            curr_sub_r = curr_sub_r->next;
                            entire_people++;
                        }
                    }
                }
            }
            
            printf(">>전체 거주자 수는 %d 명 입니다.\n", entire_people);
        }
        else if (selected == 5)
        {
            print_building();
        }
        else if (selected == 6)
        {
            printf(">>몇 번째층, 몇 번째방을 출력하시겠습니까? \n");
            scanf("%d %d", &x, &y);
            print_room(x, y);
        }
        else if (selected == 7)
        {
            printf(">>몇 번째층, 몇 번째방을 출력하시겠습니까? \n");
            scanf("%d %d", &x, &y);
            
            printf("거주자의 이름을 입력하십시오 : ");
            scanf("%s", name);
            print_sub_room(x, y, name);
        }
        else if (selected == 8)
        {
            printf("현재 돈은 %d 만원 있습니다. \n", money);
        }
        else if (selected == -1)
            break;
        else
            printf("선택지 내에서 선택해주세요.");
    }
    
    return;
}

// ==================================================
void add_floor(void)
{
    // 새로운 층을 만든다.
    int i;
    for (i=0; i<current_building_width; i++) {
        struct room new_room= {(current_building_height+1)*100 + (i+1), NULL, NULL};
        building[current_building_height][i] = new_room;
    }
    
    current_building_height++;
    printf("%d 번째 층이 추가되었습니다. \n", current_building_height);
    
    // 건설 비용으로 30만원이 지출된다.
    money = money - 30;
    return;
}


void add_room(void)
{
    // 건물의 너비를 확장한다.
    int i;
    for (i=0; i<current_building_height; i++) {
        struct room new_room= {(i+1)*100 + current_building_width+1, NULL, NULL};
        building[i][current_building_width] = new_room;
    }
    
    current_building_width++;
    printf("%d 번째 방이 추가되었습니다. \n", current_building_width);
    
    // 건설 비용으로 30만원이 지출된다.
    money = money - 30;
    return;
}

void delete_from_upper(void)
{
    // 맨 윗층을 제거한다.
    int i;
    
    if(current_building_height == 1)
    {
        printf("빌딩의 최소 높이는 3입니다. \n");
        return;
    }
    
    for (i=0; i<current_building_width; i++) {
        struct room new_room= {0, NULL, NULL};
        building[current_building_height-1][i] = new_room;
    }
    
    current_building_height--;
    
    printf("%d 번째 층이 삭제되었습니다. \n", current_building_height+1);
    
    // 제거 비용으로 10만원이 지출된다.
    money = money - 10;
    return;
}

void delete_from_side(void)
{
    // 맨 바깥쪽 방들을 제거한다.
    int i;
    
    if(current_building_width == 3)
    {
        printf("빌딩의 폭은 3 이상이어야 합니다. \n");
        return;
    }
    
    for (i=0; i<current_building_height; i++) {
        struct room new_room= {0, NULL, NULL};
        building[i][current_building_width-1] = new_room;
    }
    
    current_building_width--;
    printf("%d 번째 방이 삭제되었습니다. \n", current_building_width+1);
    
    // 제거 비용으로 10만원이 지출된다.
    money = money - 10;
    return;
}


void building_manager(void)
{
    // 건물 확장/축소에 대한 함수들을 관리하는 매니저 함수
    int selected;
    
    while (1) {
        printf("[1]-층 추가         [2]-방 추가 \n");
        printf("[3]-맨 위층 삭제    [4]-빌딩 폭 줄이기 \n");
        printf("하위 메뉴를 선택하십시오 : (종료 : -1)\n");
        
        scanf("%d", &selected);
        
        if(selected == 1)
            add_floor();
        else if(selected == 2)
            add_room();
        else if(selected == 3)
            delete_from_upper();
        else if(selected == 4)
            delete_from_side();
        else if(selected == -1)
            break;
        else
            printf("선택지 내	에서 선택해주세요.\n");
    }
    
    return;
}

// ==================================================
int print_type(void)
{
    // 타입을 선택하기 위한 정보를 출력한다.
    int i, numbers, selected;
    
    while(1)
    {
        numbers = (int)(sizeof(t_array) / sizeof(t_array[0]));
        printf(">> 몇 번째 타입으로 지정하시겠습니까? \n");
        printf("============현재 설정된 타입들============\n\n");
        for(i=0; i< numbers; i++)
        {
            printf("* %d 번째 타입. \n", i+1);
            printf("- 가격 : %d 만원, - 최대 인원수 : %d \n\n", t_array[i].price, t_array[i].max_people);
        }
        
        printf("==========================================\n");
        printf("타입 입력 : (종료 : -1 )");
        scanf("%d", &selected);
        
        if(selected > numbers)
        {
            printf(">>잘못된 선택입니다. \n");
        }else{
            break;
        }
    }
    return selected;
}

void make_room(int x, int y)
{
    // 사용자에게 타입에 대한 입력을 받고 사용 가능한 방으로 만든다.
    int room_number, selected_type;
    struct sub_room* new_s_r;
    
    selected_type = print_type();
    
    if(selected_type == -1)
        return;
    
    room_number = (x*100) + y ;
    
    if(strcmp(reserved_people[0], "") == 0)
    {
        // 새로운 방에는 항상 1명 이상 거주하고 있어야 한다.
        printf("\n\n>>예약자 명단에 아무도 없습니다. \n");
        printf(">>방에는 최소 1명 이상이 배정되어야 합니다. \n");
        printf(">>되돌아갑니다. \n");
        return;
    }
    
    // 예약자 명단에 1명 이상 존재할 경우
    
    new_s_r = (struct sub_room*) malloc(sizeof(struct sub_room));
    strcpy(new_s_r->person_name, reserved_people[0]);
    new_s_r->next = NULL;
    
    strcpy(reserved_people[0], "");
    re_booked_list();
    
    struct room new_room = {room_number, new_s_r, &t_array[selected_type-1]};
    building[x-1][y-1] = new_room;
    
    // 타입 속성중 가격 해당하는 만큼 돈이 늘어난다.
    money = money + t_array[selected_type-1].price;
    return;
}

void remove_people(int x, int y)
{
    // 특정 방에 거주하고 있는 사람을 제거한다.
    
    char name[30];
    struct room selected_room;
    struct sub_room* selected_sub_room;
    struct sub_room* prev_p;
    struct sub_room* curr_s_r;
    int max_people;
    int i, success= 0 ;
    int current_people=0;
    
    printf("제거하실 사람의 이름을 입력해주세요.");
    scanf("%s", name);
    
    selected_room = building[x-1][y-1];
    
    if(selected_room.room_type == NULL)
    {
        printf("이 방은 사람이 살고있지 않습니다. \n");
        return;
    }
    
    max_people = selected_room.room_type->max_people;
    
    selected_sub_room = selected_room.sub_r;
    curr_s_r = selected_room.sub_r;

    while(1)
    {
        // 현재 이 방에 거주하고 있는 사람 수를 계산
        if(curr_s_r == NULL)
            break;
        
        curr_s_r = curr_s_r->next;
        current_people++;
    }
    
    if(current_people == 1)
    {
        printf("\n>>방에는 최소 1명 이상 살고 있어야 합니다.\n");
        printf(">>돌아갑니다. \n");
        return;
    }
    
    for(i=0; i<max_people ; i++)
    {
        if (strcmp(selected_sub_room->person_name, name)==0)
        {
            // 링크드 리스트 노드들의 연결을 수정한다.
            if(i != 0)
                prev_p->next = selected_sub_room->next;
            else
                building[x-1][y-1].sub_r = selected_sub_room->next;
            
            success = 1;
            break;
            
        }
        
        prev_p = selected_sub_room;
        selected_sub_room = selected_sub_room->next;
    }
    
    if(success == 0)
    {
        printf("해당 방에 입력된 사람이 살고 있지 않습니다. \n");
    }else{
        printf("%s 를 제거했습니다. \n", name);
    }
    return;
}

void room_manager(void)
{
    // 방을 조작하는 함수들에 대한 매니저 함수
    int selected;
    int x,y;
    
    while(1)
    {
        printf("[1]-방 내놓기        [2]-거주자 삭제하기 \n");
        printf("하위 메뉴를 선택하십시오 : (종료 : -1)\n");
        scanf("%d", &selected);
        
        if (selected == 1)
        {
            printf("내놓고자 하는 칸을 고르시오. : \n");
            printf("(층, 칸 순서로 입력. 종료 : -1)\n");
            scanf("%d", &x);
            if(x == -1)
                // 사용자가 도중에 종료를 원했을 시
                continue;
            scanf("%d", &y);
            
            
            make_room(x, y);
        }
        else if (selected == 2)
        {
            printf("거주자를 삭제하고자 하는 칸을 고르시오. : \n");
            printf("(층, 칸 순서로 입력. 종료 : -1)\n");
            scanf("%d", &x);
            if(x == -1)
                // 사용자가 도중에 종료를 원했을 시
                continue;
            scanf("%d", &y);
            remove_people(x, y);
        }
        else if( selected == -1)
            break;
        else
            printf("선택지 내	에서 선택해주세요.\n");
    }
    
    return;
}

// ==================================================

void re_booked_list(void)
{
    // 첫번째 예약자가 빠져나가면
    // 예약자 명단 배열의 자리를 한칸씩 옮긴다.
    for (int i = 0; i < MAXIMUM_RESERVED_PEOPLE; i++)
    {
        if (strcmp(reserved_people[i], "")==0)
        {
            strcpy(reserved_people[i], reserved_people[i + 1]);
            strcpy(reserved_people[i+1], "");
        }
    }
    
    return;
}


void print_booked_list()
{
    printf("********예약자 명단**********\n");
    for (int i = 0; i < 10; i++)
    {
        if(strcmp(reserved_people[i],"") != 0)
            printf("%d.번째   %s\n", i+1, reserved_people[i]);
    }
    printf("*****************************\n");
    
}

void change_person_name(int x, int y, char* old_name)
{
    // 방에 거주하고 있는 사람중 한명을 선택해 이름을 바꾼다.
    struct sub_room* sub_r_p = building[x-1][y-1].sub_r;
    char new_name[30];
    
    int sub_r_size, i, success = 0;
    
    if(sub_r_p == NULL)
    {
        printf("선택된 방에 아무도 없습니다. \n");
        return;
    }
    
    printf("어떤 이름으로 바꾸시겠습니까?\n");
    printf(">>");
    
    scanf("%s", new_name);
    
    while(1)
    {
        if(strcmp(sub_r_p->person_name, old_name) == 0)
        {
            strcpy(sub_r_p->person_name, new_name);
            printf("이름이 변경되었습니다.\n\n");
            success = 1;
            break;
        }
        
        sub_r_p = sub_r_p->next;
    }
    
    if(success == 0)
    {
        printf("해당하는 사람을 찾지 못했습니다. \n");
    }
    
    return;
    
    
}

void set_person_to_room(int x, int y)
{
    // 예약자 명단에서 첫번째 사람을 뽑아 방에 배치한다.
    struct sub_room* sub_r_p = building[x-1][y-1].sub_r;
    struct sub_room* prev_r_p;
    int max_people = building[x-1][y-1].room_type->max_people;
    int i, sub_r_size=1;
    
    while(1)
    {
        // 현재 이 방에 거주하고 있는 사람들의 수를 계산
        if(sub_r_p == NULL)
        {
            break;
        }
        
        sub_r_p = sub_r_p->next;
        sub_r_size++;
    }
    
    if(sub_r_size > max_people)
    {
        // 타입의 최대 인원수보다 많을 때
        printf("더이상 추가할 수 없는 방입니다. \n");
        return;
    }
    
    sub_r_p = building[x-1][y-1].sub_r;
    for(i=0; i<max_people; i++)
    {
        if(sub_r_p == NULL)
        {
            // 새로운 칸을 만들어 마지막 노드에 연결한다.
            sub_r_p = (struct sub_room*) malloc(sizeof(struct sub_room));
            sub_r_p->next = NULL;
            strcpy(sub_r_p->person_name, reserved_people[0]);
            
            if(i==0)
                building[x-1][y-1].sub_r = sub_r_p;
            else
                prev_r_p->next = sub_r_p;
                
            break;
        }
        prev_r_p = sub_r_p;
        sub_r_p = sub_r_p->next;
    }
    
    strcpy(reserved_people[0], "");
    re_booked_list();
    printf("배정이 완료되었습니다.\n");
    
    return;
}

void add_reserved_person(void)
{
    // 예약자 명단에 새로운 사람을 추가한다.
    int i, success = 0;
    char name[30];
    
    print_booked_list();
    printf("추가할 예약자를 입력하세요. \n");
    
    scanf("%s", name);
    
    for(i=0; i<MAXIMUM_RESERVED_PEOPLE; i++)
    {
        if(strcmp(reserved_people[i], "")==0)
        {
            strcpy(reserved_people[i], name);
            success = 1;
            break;
        }
    }
    
    if(success == 0)
    {
        printf("\n\n>>예약자 명단이 가득 찼습니다. \n");
        printf(">>추가 실패 \n");
    }else{
        printf("\n\n>>예약자가 추가되었습니다. \n");
        
        print_booked_list();
    }
    
    return;
    
}

void del_reserved_person(void)
{
    // 예약자 명단에 있는 사람을 제거한다.
    char name[30];
    int i, success=0;
    
    print_booked_list();
    
    printf("삭제할 예약자를 입력하세요\n");
    scanf("%s", name);
    
    for(i=0; i< MAXIMUM_RESERVED_PEOPLE;i++)
    {
        if(strcmp(reserved_people[i], name) == 0)
        {
            stpcpy(reserved_people[i],"");
            success = 1;
            break;
        }
    }
    
    if(success == 0)
    {
        printf("예약자를 찾을 수 없습니다.\n");
    }else{
        printf("예약이 취소되었습니다. \n");
        
        // 한칸씩 옮긴다.
        re_booked_list();
        print_booked_list();
    }
    
    return;
    
}

void person_manager()
{
    // 예약자와 거주자를 조작하는 함수들에 대한 매니저 함수
    int x,y, selected;
    char old_name[30];
    
    while(1)
    {
        printf("[1]-거주자 이름 변경         [2]-거주자 추가(예약자 명단에서) \n");
        printf("[3]-예약자 명단에 새로 추가 [4]-예약자 명단에서 제거\n");
        printf("하위 메뉴를 선택하십시오 : (종료 : -1)\n");
        scanf("%d", &selected);
        
        if (selected == 1)
        {
            printf("바꾸고자 하는 칸을 고르시오. (몇 번째 층, 몇 번째 칸 입력) : ");
            scanf("%d %d", &x, &y);
            
            printf("변경하고자 하는 사람의 이름을 입력하세요 \n");
            scanf("%s", old_name);
            
            change_person_name(x, y, old_name);
        }
        else if (selected == 2)
        {
            printf("배정하고자 하는 칸을 입력하세요.(몇 번째 층, 몇 번째 칸 입력) : ");
            scanf("%d %d", &x, &y);
            set_person_to_room(x, y);
        }
        else if (selected == 3)
        {
            add_reserved_person();
        }else if(selected == 4){
            del_reserved_person();
        }else if(selected == -1){
            break;
        }else{
            printf("선택지 내	에서 선택해주세요.\n");
        }
    }
    
    return;
}

void print_menu(void)
{
    int x,y, selected;
    
    while(1)
    {
        printf("\n\n=========================================\n\n");
        printf("빌딩 시뮬레이션에 오신 것을 환영합니다.\n\n");
        printf("[1]-출력 관리 [2]-건물 관리 \n");
        printf("[3]-방 관리   [4]-거주자 관리\n");
        printf("\n\n=========================================\n\n");
        printf("하위 메뉴를 선택하십시오 : (종료 : -1)\n");
        scanf("%d", &selected);
        
        if (selected == 1)
        {
            print_manager();
        }
        else if (selected == 2)
        {
            building_manager();
        }
        else if (selected == 3)
        {
            room_manager();
        }
        else if(selected == 4){
            person_manager();
        }
        else if(selected == -1){
            break;
        }
        else{
            printf("선택지 내에서 선택해주세요.\n");
        }
    }
    
    return;
}

void building_initialize(void)
{
    // 맨 처음 101호, 102호, 103호 에 대한 방을 초기화한다.
    struct sub_room* s101 = (struct sub_room*) malloc(sizeof(struct sub_room));
    strcpy(s101->person_name, "Kim");
    s101->next = NULL;
    
    struct sub_room* s102 = (struct sub_room*) malloc(sizeof(struct sub_room));
    strcpy(s102->person_name, "Park");
    s102->next = NULL;
    
    struct sub_room* s103 = (struct sub_room*) malloc(sizeof(struct sub_room));
    strcpy(s103->person_name, "Lee");
    s103->next = NULL;
    
    struct room r101 = {101, s101, &t_array[0]};
    struct room r102 = {102, s102, &t_array[1]};
    struct room r103 = {103, s103, &t_array[2]};
    building[0][0] = r101;
    building[0][1] = r102;
    building[0][2] = r103;
    
    return;
}

int main(void)
{
    building_initialize();
    
    print_menu(); // 상위 메뉴 출력
    
	return 0;
}







