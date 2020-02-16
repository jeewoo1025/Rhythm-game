# Rhythm-game
* Rhythm game in C langauage    

* C언어로 만든 리듬게임      

            
Using console coordinates and Unicode, the basic rhythm game frame was created. (See Unicode Table in Wikipedia)
The full flow is the order in which "move notes → enter the first value → print full screen(note and frame) →  keyborad input and point calculation" using the "while" func.
The basic framework is a total of 5 compartments, and if you think of it as a 2-dimensional arrangement, it is frame[row][col]. ( row : 28, col : 5 )

콘솔좌표와 유니코드를 이용해서 기본 리듬게임 틀을 만들었다. (위키피디아의 유니코드표 참조)
전체 흐름은 while문을 이용해서 "노트를 이동 → 첫번째 값을 입력 → 전체 화면(노트와 틀) 출력 → 키보드 입력 및 point 계산"하는 순서이다.
기본 틀은 총 5칸이고 이것을 2차원 배열로 생각하면, frame[row][col]이다.(row : 28칸, col : 5칸)


```C
while(1)
{
            int point = 0;
                       
            move_location();
            
            input_first_value(handle, p_pos, cnt);
            cnt += 16;
            
            display_frame(handle);
            
            point = get_point(handle, max_msec);
            if(point > 0)
            {
                        total_point += point;
                        display_total_point(handle, total_point);
            }
}
```



# Documentation

If you want to know **the actual demo**, please refer to the YouTube link below.

**실제 시연 영상**이 궁금하다면 아래의 유튜브 링크를 참조하세요~:)

[C언어로 만든 리듬게임(Rhythm game in C language)](https://www.youtube.com/watch?v=08uUtbJc9VA)
