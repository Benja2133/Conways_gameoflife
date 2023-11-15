#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

struct square_t
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned int w;
    bool p;            // is the square painted?
    unsigned int nbrs; // neighbours
};
/*
(x,y)____
    |    |
    |____|
         (z,w)
*/
bool possible_pos(int pos_y, int pos_x)
{ 
    return pos_y >= 0 && pos_y < 50 && pos_x >= 0 && pos_x < 50;
    
}

void add_initial_neighbours(struct square_t arr[50][50], int posy, int posx)
{
    if (possible_pos(posy, posx - 1))
    {
        arr[posy][posx - 1].nbrs++;
    }
    if (possible_pos(posy - 1, posx))
    {
        arr[posy - 1][posx].nbrs++;
    }
    if (possible_pos(posy + 1, posx))
    {
        arr[posy + 1][posx].nbrs++;
    }

    if (possible_pos(posy - 1, posx - 1) )
    {
        arr[posy - 1][posx - 1].nbrs++;
    }
    if (possible_pos(posy + 1, posx - 1))
    {
        arr[posy + 1][posx-1].nbrs++;
    }
    if (possible_pos(posy, posx + 1))
    {
        arr[posy][posx + 1].nbrs++;
    }
    if (possible_pos(posy - 1, posx + 1))
    {
        arr[posy - 1][posx + 1].nbrs++;
    }
    if (possible_pos(posy + 1, posx + 1))
    {
        arr[posy + 1][posx + 1].nbrs++;
    }
}


void add_neighbours(int arr[50][50], int posy, int posx)
{
    if (possible_pos(posy, posx - 1))
    {
        arr[posy][posx - 1]++;
    }
    if (possible_pos(posy - 1, posx))
    {
        arr[posy - 1][posx]++;
    }
    if (possible_pos(posy + 1, posx))
    {
        arr[posy + 1][posx]++;
    }

    if (possible_pos(posy - 1, posx - 1) )
    {
        arr[posy - 1][posx - 1]++;
    }
    if (possible_pos(posy + 1, posx - 1))
    {
        arr[posy + 1][posx-1]++;
    }
    if (possible_pos(posy, posx + 1))
    {
        arr[posy][posx + 1]++;
    }
    if (possible_pos(posy - 1, posx + 1))
    {
        arr[posy - 1][posx + 1]++;
    }
    if (possible_pos(posy + 1, posx + 1))
    {
        arr[posy + 1][posx + 1]++;
    }
}

void take_neighbours(int arr[50][50], int posy, int posx)
{
  if (possible_pos(posy, posx - 1))
    {
        arr[posy][posx - 1]--;
    }
    if (possible_pos(posy - 1, posx))
    {
        arr[posy - 1][posx]--;
    }
    if (possible_pos(posy + 1, posx))
    {
        arr[posy + 1][posx]--;
    }

    if (possible_pos(posy - 1, posx - 1) )
    {
        arr[posy - 1][posx - 1]--;
    }
    if (possible_pos(posy + 1, posx - 1))
    {
        arr[posy + 1][posx-1]--;
    }
    if (possible_pos(posy, posx + 1))
    {
        arr[posy][posx + 1]--;
    }
    if (possible_pos(posy - 1, posx + 1))
    {
        arr[posy - 1][posx + 1]--;
    }
    if (possible_pos(posy + 1, posx + 1))
    {
        arr[posy + 1][posx + 1]--;
    }
}


void check_and_change(struct square_t arr[50][50],int new_nbrs[50][50])
{
    for (unsigned int i = 0; i < 50; ++i) // fila i
    {
        for (unsigned int j = 0; j < 50; ++j) // columna j
        {
            if (arr[i][j].p == true) {
                if (arr[i][j].nbrs < 2 || arr[i][j].nbrs > 3) {
                    // Muere por soledad o sobrepoblación
                    al_draw_filled_rectangle(arr[i][j].x, arr[i][j].y,
                                             arr[i][j].z, arr[i][j].w, al_map_rgb(0, 0, 0));
                    arr[i][j].p = false;
                    take_neighbours(new_nbrs, i, j);
                }
            } else {
                if (arr[i][j].nbrs == 3) {
                    // Nace una nueva célula
                    al_draw_filled_rectangle(arr[i][j].x, arr[i][j].y,
                                             arr[i][j].z, arr[i][j].w, al_map_rgb(255, 255, 255));
                                             
                    //printf("se pinta el cuadrado arr[i][j].x= %u, arr[i][j].y=%u, arr[i][j].z=%u, arr[i][j].w=%u\n",arr[i][j].x, arr[i][j].y,  arr[i][j].z, arr[i][j].w);
                    arr[i][j].p = true;
                    add_neighbours(new_nbrs, i, j);
                }
            }
        }
    }


}

void update_nbrs(struct square_t sq_arr[50][50],int new_nbrs[50][50])
{
    for (unsigned int i = 0; i < 50; ++i) // fila i
    {
        for (unsigned int j = 0; j < 50; ++j) // columna j
        {
            sq_arr[i][j].nbrs += new_nbrs[i][j];
            new_nbrs[i][j]=0;
        }
    }
}

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();

    struct square_t squaremap[50][50];
    int new_nbrs[50][50];

    unsigned int x_value = 0;
    unsigned int y_value = 0;
    unsigned int z_value = 10;
    unsigned int w_value = 10;

    for (unsigned int i = 0; i < 50; ++i) // fila i
    {
        for (unsigned int j = 0; j < 50; ++j) // columna j
        {
            new_nbrs[i][j] = 0;
            squaremap[i][j].nbrs = 0;
            squaremap[i][j].p = false;
            squaremap[i][j].x = x_value;
            squaremap[i][j].y = y_value;
            squaremap[i][j].z = z_value;
            squaremap[i][j].w = w_value;
            x_value += 10;
            z_value += 10;
        }
        y_value += 10;
        w_value += 10;
        x_value = 0;
        z_value = 10;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 10.0 );
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *disp = al_create_display(500, 500);
    ALLEGRO_FONT *font = al_create_builtin_font();

    al_init_primitives_addon();
    /*unsigned int coor_x = 0;
    unsigned int coor_y = 0;


    printf("colocar una coordenada\n");
    printf("x:");
    scanf("%u", &coor_x);
    printf("\ny:");
    scanf("%u", &coor_y);
    al_draw_filled_rectangle(squaremap[coor_x][coor_y].x,squaremap[coor_x][coor_y].y,
    squaremap[coor_x][coor_y].z,squaremap[coor_x][coor_y].w,al_map_rgb(255,255,255));
*/
    //al_draw_filled_rectangle(10,0,20,10,al_map_rgb(255,255,255));


    //al_flip_display();

    //sleep(4);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    unsigned int pos_x, pos_y;
    // momento de poner el patron:
    while (event.keyboard.keycode != ALLEGRO_KEY_ENTER)
    {
        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            goto end;

        al_wait_for_event(queue, &event);

        if (redraw && al_is_event_queue_empty(queue))
        {
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                pos_x = (unsigned int)event.mouse.x / 10;
                pos_y = (unsigned int)event.mouse.y / 10;
                printf("x:%u , y:%u \n", pos_x, pos_y);
                if (squaremap[pos_y][pos_x].p == false)
                {
                    al_draw_filled_rectangle(squaremap[pos_y][pos_x].x, squaremap[pos_y][pos_x].y,
                                             squaremap[pos_y][pos_x].z, squaremap[pos_y][pos_x].w, al_map_rgb(255, 255, 255));

                    squaremap[pos_y][pos_x].p = true;

                    add_initial_neighbours(squaremap, pos_y, pos_x);
                }

                printf("num vecinos del cuadrado:%u\n", squaremap[pos_y][pos_x].nbrs);
            }
            al_flip_display();
            redraw = false;
        }
    }
    // comienza el juego ...
    while (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            check_and_change(squaremap,new_nbrs);
            update_nbrs(squaremap,new_nbrs);
            al_flip_display();
            sleep(0.1);
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    end:
    return 0;
}
