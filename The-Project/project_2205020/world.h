#include "iGraphics.h"

double road_x[6] = {715, 715, 1430, 1430, 0 ,0}, road_y[6] = {720, 720, 50, 0, 0, 50};
double horizon_x1 = 0, horizon_x2 = 1430, horizon_y1 = 720, horizon_y2 = 720;
double depth = 1000, log_base = pow(depth, 1/horizon_y1);
double sky_x = horizon_x1, sky_dx = 1430, sky_y = horizon_y1, sky_dy = 860 - horizon_y1;
double railing[2][3][3] = {{{road_x[0], road_x[5], road_x[5]}, {road_y[0], road_y[5], road_y[5]+175}}, 
                           {{road_x[1], road_x[2], road_x[2]}, {road_y[1], road_y[2], road_y[2]+175}}};
double world_dx_dy = 1430/ horizon_y1, d_dz = 1 / depth;
double global_depth = 0, view_height = depth/10, f_line_z = -100000, health_bar_width = 300, health_bar_height = 50;
double road_strip_z = -2400, road_strip_dx = 50, road_side_strip_dx = 260, road_strip_dz = depth/20, road_strip_dy = 90, road_strip_x = 715;
double player_car_v = 0, player_car_a = 0.1, friction_a = 0.015, max_v = 23, max_health = 1.00, curr_health = 1.0;
char car_image[2][40][35] = {{"images\\cars\\car_1\\x_0.bmp", "images\\cars\\car_1\\x_0-.bmp", "images\\cars\\car_1\\x_1.bmp", "images\\cars\\car_1\\x_1-.bmp", "images\\cars\\car_1\\x_2.bmp", "images\\cars\\car_1\\x_2-.bmp", "images\\cars\\car_1\\x_3.bmp", "images\\cars\\car_1\\x_3-.bmp", "images\\cars\\car_1\\x_4.bmp", "images\\cars\\car_1\\x_4-.bmp",
                              "images\\cars\\car_1\\x_5.bmp", "images\\cars\\car_1\\x_5-.bmp", "images\\cars\\car_1\\x_6.bmp", "images\\cars\\car_1\\x_6-.bmp", "images\\cars\\car_1\\x_7.bmp", "images\\cars\\car_1\\x_7-.bmp", "images\\cars\\car_1\\x_8.bmp", "images\\cars\\car_1\\x_8-.bmp", "images\\cars\\car_1\\x_9.bmp", "images\\cars\\car_1\\x_9-.bmp",
                              "images\\cars\\car_1\\x_10.bmp", "images\\cars\\car_1\\x_10-.bmp", "images\\cars\\car_1\\x_11.bmp", "images\\cars\\car_1\\x_11-.bmp", "images\\cars\\car_1\\x_12.bmp", "images\\cars\\car_1\\x_12-.bmp", "images\\cars\\car_1\\x_13.bmp", "images\\cars\\car_1\\x_13-.bmp", "images\\cars\\car_1\\x_14.bmp", "images\\cars\\car_1\\x_14-.bmp",
                              "images\\cars\\car_1\\x_15.bmp", "images\\cars\\car_1\\x_15-.bmp", "images\\cars\\car_1\\x_16.bmp", "images\\cars\\car_1\\x_16-.bmp", "images\\cars\\car_1\\x_17.bmp", "images\\cars\\car_1\\x_17-.bmp", "images\\cars\\car_1\\x_18.bmp", "images\\cars\\car_1\\x_18-.bmp", "images\\cars\\car_1\\x_19.bmp", "images\\cars\\car_1\\x_19-.bmp"},
                             {"images\\cars\\car_2\\x_0.bmp", "images\\cars\\car_2\\x_1.bmp", "images\\cars\\car_2\\x_2.bmp", "images\\cars\\car_2\\x_3.bmp", "images\\cars\\car_2\\x_4.bmp", "images\\cars\\car_2\\x_5.bmp", "images\\cars\\car_2\\x_6.bmp", "images\\cars\\car_2\\x_7.bmp", "images\\cars\\car_2\\x_8.bmp", "images\\cars\\car_2\\x_9.bmp",
                              "images\\cars\\car_2\\x_10.bmp", "images\\cars\\car_2\\x_11.bmp", "images\\cars\\car_2\\x_12.bmp", "images\\cars\\car_2\\x_13.bmp", "images\\cars\\car_2\\x_14.bmp", "images\\cars\\car_2\\x_15.bmp", "images\\cars\\car_2\\x_16.bmp", "images\\cars\\car_2\\x_17.bmp", "images\\cars\\car_2\\x_18.bmp", "images\\cars\\car_2\\x_19.bmp",
                              "images\\cars\\car_2\\x_20.bmp", "images\\cars\\car_2\\x_21.bmp", "images\\cars\\car_2\\x_22.bmp", "images\\cars\\car_2\\x_23.bmp", "images\\cars\\car_2\\x_24.bmp", "images\\cars\\car_2\\x_25.bmp", "images\\cars\\car_2\\x_26.bmp", "images\\cars\\car_2\\x_27.bmp", "images\\cars\\car_2\\x_28.bmp", "images\\cars\\car_2\\x_29.bmp",
                              "images\\cars\\car_2\\x_30.bmp", "images\\cars\\car_2\\x_31.bmp", "images\\cars\\car_2\\x_32.bmp", "images\\cars\\car_2\\x_33.bmp", "images\\cars\\car_2\\x_34.bmp", "images\\cars\\car_2\\x_35.bmp", "images\\cars\\car_2\\x_36.bmp", "images\\cars\\car_2\\x_37.bmp", "images\\cars\\car_2\\x_38.bmp", "images\\cars\\car_2\\x_39.bmp"}},
     view = 'n', car_view_mode = 'd';//i for image and d for draw

//finish_line
typedef struct finish_line{
    double finish_line_dy = 450, finish_line_z, finish_line_dx = 1500;
    double pillar_dx = 30, pillar_dy = 750;
} finish_line;

//car portion
typedef struct car{
    double car_x = 715, car_y = 50, car_z = depth, car_dy = 120, car_dx = 400, side_movement = 25, health = 0.5;
    double velocity = 0, acceleration = 0.08, max = 12, max_2; int car_chosen = 1, color_factor = 1;
} car;

typedef struct point{
    double coin_freq = 4.00*sqrt(diff_fact), boost_x[2] = {350, 1100};
    double z = 0, x[2] = {350, 1100}, value = 50, radius = 80, height = 200, barrier_dz = 800, barrier_width = 500, barrier_height = 350, barrier_strip_height = barrier_height/6, boost_z = -50;
    int rand = 0, boost_rand = 1; 

} point;

void draw_health_bar(){
    iSetColor(256, 256, 256);
    iFilledRectangle(50, 500, health_bar_width, health_bar_height);
    double dx = curr_health/max_health;
    if(dx> 0 && dx < 0.3) iSetColor(180, 0, 0); if(dx >= 0.3 && dx < 0.6) iSetColor(253, 253, 3); if(dx >= 0.6 && dx <= 1.00) iSetColor(0, 180, 0);
    iFilledRectangle(50, 500, health_bar_width * dx, health_bar_height);
    iSetColor(0, 0, 0), iRectangle(50, 500, health_bar_width, health_bar_height);
    iSetColor(0, 0, 0), iText(100, 520, "Car Health...", GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_point_bar(){
    iSetColor(255, 255, 255), iFilledRectangle(1090, 500, 150, 50), iSetColor(0, 0, 0), iRectangle(1090, 500, 150, 50);
    iText(1100, 520, "Coins: ", GLUT_BITMAP_TIMES_ROMAN_24);
    char coins[2]; sprintf(coins, "%d", point_collected);
    iText(1180, 520, coins, GLUT_BITMAP_TIMES_ROMAN_24);
}

void drive_n_draw_point_n_barrier(point* p, car* pc, finish_line* f, int random = 1){
    invincible -= (invincible > 0)? 1*diff_fact: 0;
    char draw_point = 'y';
    if((int)p->z%(int)(depth*p->coin_freq) >= 0 && (int)p->z%(int)(depth*p->coin_freq) < 100) iSetColor(255, 255, 255), iText(600, 400, "Coin Ahead ! Remeber barrier !", GLUT_BITMAP_TIMES_ROMAN_24);
    if(quit_game_ask == 'n') p->z += player_car_v;
    if(p->z >= depth * p->coin_freq) p->z = -100;
    if(p->z < 0 || p->z-p->barrier_dz > depth+player_car_v/2) p->rand = (int)(player_car_v*random)%2;
    //checking if hit
    if(p->z >= depth-player_car_v/2 && p->z <= depth+player_car_v/2 && p->x[p->rand]+p->radius >= pc->car_x && p->x[p->rand]-p->radius <= pc->car_x + pc->car_dx && f->finish_line_z < depth) point_collected++, draw_point = 'n'; 
    if(invincible <= 0 && p->z - p->barrier_dz >= depth-player_car_v/2 && p->z - p->barrier_dz <= depth+player_car_v/2 && p->x[p->rand]+(p->barrier_width)/2 >= pc->car_x && p->x[p->rand]-(p->barrier_width)/2 <= pc->car_x + pc->car_dx-20 && f->finish_line_z < depth) hit_got++, curr_health += health_per_hit * player_car_v/max_v, player_car_v /= 1.2*diff_fact;
    //draw barrier
    double y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(p->z-p->barrier_dz)*(p->z-p->barrier_dz)*horizon_y1*horizon_y1)/(depth*depth)), x_for_drawing = (715 - p->x[p->rand]+p->barrier_width/2)*(y_for_drawing-horizon_y1)/horizon_y1+715;
    if(p->z - p->barrier_dz > 0){
        iSetColor(250, 1, 1);
        iFilledRectangle(x_for_drawing, y_for_drawing+p->barrier_strip_height*(1-y_for_drawing/horizon_y1), p->barrier_width*(1-y_for_drawing/horizon_y1), p->barrier_strip_height*(1-y_for_drawing/horizon_y1));
        iFilledRectangle(x_for_drawing, y_for_drawing+5*p->barrier_strip_height*(1-y_for_drawing/horizon_y1), p->barrier_width*(1-y_for_drawing/horizon_y1), p->barrier_strip_height*(1-y_for_drawing/horizon_y1));
        iSetColor(256, 256, 256);
        iFilledRectangle(x_for_drawing, y_for_drawing+3*p->barrier_strip_height*(1-y_for_drawing/horizon_y1), p->barrier_width*(1-y_for_drawing/horizon_y1), p->barrier_strip_height*(1-y_for_drawing/horizon_y1));
    }
    //draw coin
    if(draw_point == 'y'){
        y_for_drawing = log(depth - p->z)/log(log_base), x_for_drawing = (715 - p->x[p->rand])*(y_for_drawing-horizon_y1)/horizon_y1+715;
        //y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(p->z)*(p->z)*horizon_y1*horizon_y1)/(depth*depth)), x_for_drawing = (715 - p->x[p->rand])*(y_for_drawing-horizon_y1)/horizon_y1+715;
        iSetColor(200, 150, 2), iFilledCircle(x_for_drawing, y_for_drawing, (1-y_for_drawing/horizon_y1)*p->radius, 200);
        iSetColor(251, 201, 4);
        iFilledCircle(x_for_drawing, y_for_drawing, (1-y_for_drawing/horizon_y1)*p->radius*0.7, 100);
    }
}

void drive_n_draw_boost(point* p, car* pc, finish_line* f, int random = 3){
    if(p->boost_z >= -37 && p->boost_z <= 200) iSetColor(255, 255, 255), iText(600, 500, "Boost Ahead ! Increase Health!", GLUT_BITMAP_TIMES_ROMAN_24);
    if(quit_game_ask == 'n') p->boost_z += player_car_v;
    if(p->boost_z >= depth * p->coin_freq * 4) p->boost_z = -37;
    if(p->boost_z < 0 || p->boost_z > depth+player_car_v/2) p->boost_rand = (int)(player_car_v*random+1)%2;
    //checking if hit
    if(p->boost_z >= depth-player_car_v/2 && p->boost_z <= depth+player_car_v/2 && p->boost_x[p->boost_rand]+p->radius >= pc->car_x && p->boost_x[p->boost_rand]-p->radius <= pc->car_x + pc->car_dx && f->finish_line_z < depth) curr_health += (curr_health+0.2 <= max_health)? 0.2/diff_fact: 0, invincible = 1000;

    //drawing
    double y_for_drawing = log(depth - p->boost_z)/log(log_base), x_for_drawing = (715 - p->boost_x[p->boost_rand])*(y_for_drawing-horizon_y1)/horizon_y1+715;
    //y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(p->z)*(p->z)*horizon_y1*horizon_y1)/(depth*depth)), x_for_drawing = (715 - p->x[p->rand])*(y_for_drawing-horizon_y1)/horizon_y1+715;
    iSetColor(154, 191, 207), iFilledCircle(x_for_drawing, y_for_drawing, (1-y_for_drawing/horizon_y1)*p->radius, 200);
    iSetColor(195, 217, 227), iFilledCircle(x_for_drawing, y_for_drawing, (1-y_for_drawing/horizon_y1)*p->radius*0.7, 100);
    iSetColor(214, 60, 155), 
    iFilledRectangle(x_for_drawing-(1-y_for_drawing/horizon_y1)*p->radius*0.3, y_for_drawing-(1-y_for_drawing/horizon_y1)*p->radius*0.6, (1-y_for_drawing/horizon_y1)*0.6*p->radius, (1-y_for_drawing/horizon_y1)*1.2*p->radius), 
    iFilledRectangle(x_for_drawing-(1-y_for_drawing/horizon_y1)*p->radius*0.6, y_for_drawing-(1-y_for_drawing/horizon_y1)*p->radius*0.3, (1-y_for_drawing/horizon_y1)*p->radius*1.2, (1-y_for_drawing/horizon_y1)*p->radius*0.6);
}

void draw_invincibility_bar(){
    iSetColor(255, 255, 255), iFilledRectangle(50, 400, health_bar_width, health_bar_height); 
    iSetColor(255*(1-invincible/1000), 255*invincible/1000, 0);
    if(invincible > 0) iFilledRectangle(51, 401, health_bar_width*invincible/1000-2, health_bar_height-2);
    iSetColor(0, 0, 0), iText(90, 420, "Invincibility...", GLUT_BITMAP_TIMES_ROMAN_24);
}

void draw_speedometer(){
    double x = 1200, y = 0, r = 180, speed_theta = 3.14159*player_car_v/max_v;
    iSetColor(250, 250, 250);
    iFilledCircle(x, y, r+30, 500);
    iSetColor(180, 180, 100);
    iFilledCircle(x, y, r, 500);
    iSetColor(10, 10, 10);
    iText(x-40, 50, "SPEED (km/h)", GLUT_BITMAP_HELVETICA_18);
    for(int i=0; i<7; i++){
        char speed[4]; sprintf(speed, "%d", 0+50*i);
        double theta = 3.14159*i/6;
        iText(x-r*cos(theta)-10, y+r*sin(theta), speed, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    double reader[2][3]={{x-3*sin(speed_theta), x-(r-5)*cos(speed_theta), x+3*sin(speed_theta)},{0-3*cos(speed_theta), y+(r-5)*sin(speed_theta),0+3*cos(speed_theta)}};
    iSetColor(256, 10, 50);
    iFilledPolygon(reader[0], reader[1], 3);
    iSetColor(10, 10, 10);
    iFilledCircle(x, y, 18, 500);
}

void draw_progress_bar(finish_line* f){
    double progress = (f->finish_line_z - f_line_z/diff_fact)/(depth-f_line_z/diff_fact), total_progress = 300;
    //draw bar
    iSetColor(256, 256, 256);
    iFilledRectangle(1000, 650, total_progress, 50);
    iSetColor(0, 0, 0);
    iRectangle(1000, 650, total_progress, 50);
    iSetColor(0, 256, 10);
    iFilledRectangle(1001, 651, total_progress*progress, 47);
    if(view == 'n') iSetColor(256, 256, 256);
    else iSetColor(2, 2, 50);
    iText(990, 630, "GO", GLUT_BITMAP_HELVETICA_18), iText(950+total_progress, 630, "VICTORY", GLUT_BITMAP_HELVETICA_18);
    iSetColor(0, 0, 0), iText(960+total_progress*progress, 670, "YOU", GLUT_BITMAP_HELVETICA_18);
}

void drive_player_car(car*c, char k){
    if(player_car_v > 0) player_car_v -= (c->car_x < 0 || c->car_x > 1200)? 1.5*friction_a*(1-0.5*player_car_v/max_v)*diff_fact :friction_a*(1-0.5*player_car_v/max_v);
    if(k == 'w' || k == GLUT_KEY_UP) player_car_v += (player_car_v < max_v*curr_health)? player_car_a*(1-0.855*player_car_v/max_v)*sqrt(curr_health) : 0;
    else if((k == 'a' || k == GLUT_KEY_LEFT) && player_car_v > 0 && c->car_x > -200) c->car_x -= c->side_movement*sqrt(player_car_v/max_v);
    else if((k == 'd' || k == GLUT_KEY_RIGHT) && player_car_v > 0 && c->car_x < 1200) c->car_x += c->side_movement*sqrt(player_car_v/max_v);
    else if(k == 'q' && player_car_v > 0) player_car_v += player_car_a, c->car_x -= c->side_movement*sqrt(player_car_v/max_v);
    else if(k == 'e' && player_car_v > 0) player_car_v += player_car_a, c->car_x += c->side_movement*sqrt(player_car_v/max_v);
    else if(k == 's' || k == GLUT_KEY_DOWN) player_car_v -= (player_car_v>0)? player_car_a*2 : 0;
}

void draw_car(car c){
    double z = depth - c.car_z;
    double y_for_drawing = log(z)/log(log_base), x_for_drawing = (715 - c.car_x)*(y_for_drawing-horizon_y1)/horizon_y1+715;
    int im = ((int)y_for_drawing/18 >= 0 && (int)y_for_drawing/18 < 40)? (int)y_for_drawing/18 : ((int)y_for_drawing/18 < 0)? 0: 39;
    if(c.car_z > 0 && c.car_z<= depth+100){
        if(car_view_mode == 'i') iShowBMP2(x_for_drawing, y_for_drawing, car_image[c.car_chosen][im], 0);
        else if(car_view_mode == 'd'){
            double car_top[2][4] = {{x_for_drawing, x_for_drawing+c.car_dx*(1-y_for_drawing/horizon_y1), x_for_drawing+(c.car_dx-99)*(1-y_for_drawing/horizon_y1),x_for_drawing+99*(1-y_for_drawing/horizon_y1)},{y_for_drawing+c.car_dy*(1-y_for_drawing/horizon_y1), y_for_drawing+c.car_dy*(1-y_for_drawing/horizon_y1), y_for_drawing+(c.car_dy+50)*(1-y_for_drawing/horizon_y1), y_for_drawing+(c.car_dy+50)*(1-y_for_drawing/horizon_y1)}};
            double hood[2][4] = {{x_for_drawing+(c.car_dx-59)*(1-y_for_drawing/horizon_y1), x_for_drawing+59*(1-y_for_drawing/horizon_y1), x_for_drawing+84*(1-y_for_drawing/horizon_y1), x_for_drawing+(c.car_dx-84)*(1-y_for_drawing/horizon_y1)}, {y_for_drawing+c.car_dy*(1-y_for_drawing/horizon_y1), y_for_drawing+c.car_dy*(1-y_for_drawing/horizon_y1), y_for_drawing+(c.car_dy+110)*(1-y_for_drawing/horizon_y1), y_for_drawing+(c.car_dy+110)*(1-y_for_drawing/horizon_y1)}};
            double lights[2][3] = {{x_for_drawing+20*(1-y_for_drawing/horizon_y1), y_for_drawing+50*(1-y_for_drawing/horizon_y1), 15*(1-y_for_drawing/horizon_y1)},{car_top[0][1]-20*(1-y_for_drawing/horizon_y1), y_for_drawing+50*(1-y_for_drawing/horizon_y1), 15*(1-y_for_drawing/horizon_y1)}};
            double wheels[2][4] = {{x_for_drawing, y_for_drawing-80*(1-y_for_drawing/horizon_y1), 80*(1-y_for_drawing/horizon_y1), 80*(1-y_for_drawing/horizon_y1)}, {car_top[0][1]-80*(1-y_for_drawing/horizon_y1), y_for_drawing-80*(1-y_for_drawing/horizon_y1), 80*(1-y_for_drawing/horizon_y1), 80*(1-y_for_drawing/horizon_y1)}};
            //drawing car body
            iSetColor(28*(c.color_factor+1), 255/(c.color_factor+1), 100+c.color_factor*c.color_factor);
            iFilledRectangle(x_for_drawing, y_for_drawing, c.car_dx*(1-y_for_drawing/horizon_y1), c.car_dy*(1-y_for_drawing/horizon_y1));
            //drawing car top
            iSetColor(256, 256, 256);
            iFilledPolygon(car_top[0], car_top[1],4);
            //drawing car hood
            iSetColor(80, 200, 220);
            iFilledPolygon(hood[0], hood[1], 4);
            iSetColor(0,0,0);
            iPolygon(hood[0], hood[1], 4);
            //drawing car back lights
            iSetColor(0,0,0);
            iCircle(lights[0][0], lights[0][1], lights[0][2]);
            iCircle(lights[1][0], lights[1][1], lights[1][2]);
            iSetColor(250,0,0);
            iFilledCircle(lights[0][0], lights[0][1], lights[0][2]);
            iFilledCircle(lights[1][0], lights[1][1], lights[1][2]);
            //drawing car wheels
            iSetColor(0, 0, 0);
            iFilledRectangle(wheels[0][0], wheels[0][1], wheels[0][2], wheels[0][3]);
            iFilledRectangle(wheels[1][0], wheels[1][1], wheels[1][2], wheels[1][3]);
        }
        //car health bar
        iSetColor(255, 255, 255), iFilledRectangle(x_for_drawing+120*(1-y_for_drawing/horizon_y1), y_for_drawing+300*(1-y_for_drawing/horizon_y1), 150*(1-y_for_drawing/horizon_y1), 30*(1-y_for_drawing/horizon_y1));
        double dx = c.health/max_health;
        if(dx> 0 && dx < 0.3) iSetColor(180, 0, 0); if(dx >= 0.3 && dx < 0.6) iSetColor(253, 253, 3); if(dx >= 0.6 && dx <= 1.00) iSetColor(0, 180, 0);
        iFilledRectangle(x_for_drawing+120*(1-y_for_drawing/horizon_y1), y_for_drawing+300*(1-y_for_drawing/horizon_y1), 149*(1-y_for_drawing/horizon_y1)*dx, 30*(1-y_for_drawing/horizon_y1));
        iSetColor(0, 0, 0), iRectangle(x_for_drawing+120*(1-y_for_drawing/horizon_y1), y_for_drawing+300*(1-y_for_drawing/horizon_y1), 150*(1-y_for_drawing/horizon_y1), 30*(1-y_for_drawing/horizon_y1));
    }
}

void drive_car(car* c, car* pc, finish_line* f, int random = 3){
    if(c->car_z < depth) c->velocity += (c->velocity < c->max)? c->acceleration*(1-c->velocity/c->max)*c->health: 0;
    else c->velocity += (c->velocity < c->max_2)? c->acceleration*(1-c->velocity/c->max_2)*c->health: 0;
    c->car_z += player_car_v - c->velocity;
    if(c->car_z >= depth-player_car_v/2 && c->car_z <= depth+player_car_v/2 && c->car_x+(c->car_dx) >= pc->car_x && c->car_x <= pc->car_x + pc->car_dx && f->finish_line_z < depth) 
        if(c->car_z < depth) curr_health += health_per_hit * player_car_v/max_v, player_car_v /= 1.2*diff_fact, c->health -= 0.1/diff_fact;
        else if(c->car_z >= depth) c->velocity /= 5*diff_fact, c->health -= 0.3*pow(diff_fact, 1/3);
    if(c->car_z < 0 || c->car_z > depth) c->car_x += ((int)(player_car_v+random)%2 && c->car_x+c->side_movement < 1000)? +c->side_movement: (c->car_x-c->side_movement > 0)? -c->side_movement : 0;
}

void drive_n_draw_road_strip(char key){
    if(quit_game_ask == 'n') road_strip_z -= player_car_v;

    double start_z = (int)(0-road_strip_z)%(2*(int)road_strip_dz);

    for(int i = 0; i <= depth/(2*road_strip_dz); i++){
        iSetColor(250, 250, 250);
        double y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(start_z+i*2*road_strip_dz)*(start_z+i*2*road_strip_dz)*horizon_y1*horizon_y1)/(depth*depth)), 
        //double y_for_drawing = log(start_z+i*2*road_strip_dz - depth)/log(log_base),
        x_for_drawing = (715 - road_strip_x)*(y_for_drawing-horizon_y1)/horizon_y1+715;
        iFilledRectangle(x_for_drawing, y_for_drawing, road_strip_dx*(1-y_for_drawing/horizon_y1), road_strip_dy*(1-y_for_drawing/horizon_y1));
        iSetColor(209, 39, 39);

        double left_strip[2][4] = {{715*y_for_drawing/horizon_y1-50*(1-y_for_drawing/horizon_y1), 
        715*y_for_drawing/horizon_y1-50*(1-y_for_drawing/horizon_y1)-road_side_strip_dx*(1-y_for_drawing/horizon_y1), 
        715*y_for_drawing/horizon_y1-road_side_strip_dx*(1-y_for_drawing/horizon_y1) + (road_strip_dy-30)*(1-y_for_drawing/horizon_y1), 
        715*y_for_drawing/horizon_y1+(road_strip_dy-50)*(1-y_for_drawing/horizon_y1)},
        
        {y_for_drawing, y_for_drawing, y_for_drawing+road_strip_dy*(1-y_for_drawing/horizon_y1),  y_for_drawing+road_strip_dy*(1-y_for_drawing/horizon_y1)}};


        double right_strip[2][4] = {{1430-(715*y_for_drawing/horizon_y1-50*(1-y_for_drawing/horizon_y1)), 
        1430-(715*y_for_drawing/horizon_y1-50*(1-y_for_drawing/horizon_y1)-road_side_strip_dx*(1-y_for_drawing/horizon_y1)), 
        1430-(715*y_for_drawing/horizon_y1-road_side_strip_dx*(1-y_for_drawing/horizon_y1) + (road_strip_dy-30)*(1-y_for_drawing/horizon_y1)), 
        1430-(715*y_for_drawing/horizon_y1+(road_strip_dy-50)*(1-y_for_drawing/horizon_y1))},
        
        {y_for_drawing, y_for_drawing, y_for_drawing+road_strip_dy*(1-y_for_drawing/horizon_y1),  y_for_drawing+road_strip_dy*(1-y_for_drawing/horizon_y1)}};

        iFilledPolygon(left_strip[0], left_strip[1], 4);
        iFilledPolygon(right_strip[0], right_strip[1], 4);
    }
}

void drive_n_draw_finish_line(finish_line* f, char key){
    if(quit_game_ask == 'n') f->finish_line_z += player_car_v;
    if(f->finish_line_z > 0 && f->finish_line_z <= depth+100){
        double z = depth - f->finish_line_z;
        //double y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(z-depth)*(z-depth)*horizon_y1*horizon_y1)/(depth*depth)), 
        double y_for_drawing = log(z)/log(log_base), x_for_drawing = y_for_drawing*715/horizon_y1;
        //pillars
        iSetColor(0, 0, 0);
        iFilledRectangle(x_for_drawing-f->pillar_dx*(1-y_for_drawing/horizon_y1), y_for_drawing, f->pillar_dx*(1-y_for_drawing/horizon_y1), f->pillar_dy*(1-y_for_drawing/horizon_y1));
        iFilledRectangle(x_for_drawing+(f->pillar_dx+1430)*(1-y_for_drawing/horizon_y1), y_for_drawing, f->pillar_dx*(1-y_for_drawing/horizon_y1), f->pillar_dy*(1-y_for_drawing/horizon_y1));
        //banner
        iSetColor(256, 256, 256);
        iFilledRectangle(x_for_drawing-f->pillar_dx*(1-y_for_drawing/horizon_y1), y_for_drawing+f->pillar_dy*(1-y_for_drawing/horizon_y1), f->finish_line_dx*(1-y_for_drawing/horizon_y1), f->finish_line_dy*(1-y_for_drawing/horizon_y1));
    };
}

void draw_world(char key){
    //draw the base world matrix with sand color, night time darkkkkk sea
	if(view == 'n') iSetColor(7, 1, 36);//night
    else iSetColor(193, 241, 246);//day
	iFilledRectangle(0, 0, 1430, 860);
    //draw shore
    double shore[2][2][3] = {{{715, 0, 0}, {horizon_y1, 400, 200}}, {{715, 1430, 1430}, {horizon_y1, 400, 200}}};
    if(view == 'n') iSetColor(38, 42, 3);//night
    else iSetColor(27, 188, 81);//day
    iFilledPolygon(shore[0][0], shore[0][1],3), iFilledPolygon(shore[1][0], shore[1][1], 3);
    iLine(715, horizon_y1, 0, 400); iLine(715, horizon_y1, 1430, 400);
    //draw the road
    //if(view == 'n') 
    iSetColor(50, 50, 50);//night
    //else iSetColor(60, 60, 60);//day
	iFilledPolygon(road_x, road_y, 6);
    //draw road side and center strips;
    if(view == 'n') iSetColor(200, 200, 200);//night
    else iSetColor(230, 230, 230);//day
    iFilledPolygon(railing[0][0], railing[0][1], 3);
    iFilledPolygon(railing[1][0], railing[1][1], 3);
    drive_n_draw_road_strip(key);
    //draw horizon and sky
    if(view == 'n') iSetColor(10, 2, 24);//night
    else iSetColor(180, 236, 255);//day
	iFilledRectangle(sky_x, sky_y, sky_dx, sky_dy);
    if(view == 'n') iSetColor(55, 55, 55);//night
    else iSetColor(50, 180, 100);//day
    iLine(horizon_x1, horizon_y1, horizon_x2, horizon_y2);
    //draw moon and stars, let it be a starry night, or sun and clouds
    if(view == 'n'){
        iSetColor(256, 256, 256), iFilledCircle(700, horizon_y1+100, 20, 300);
        iFilledCircle(500, 750, 1), iFilledCircle(550, 760, 1), iFilledCircle(620, 730, 1), iFilledCircle(625, 800, 1),
        iFilledCircle(1200, 750, 1), iFilledCircle(1020, 790, 1), iFilledCircle(1000, 850, 1), iFilledCircle(300, 775, 1),
        iFilledCircle(460, 805, 1), iFilledCircle(1300, 725, 1), iFilledCircle(1380, 830, 1), iFilledCircle(720, 750, 1),
        iFilledCircle(740, 740, 1), iFilledCircle(760, 785, 1);
        iSetColor(10, 2, 24), iFilledCircle(705, horizon_y1+108, 20, 300);
    }
    else{
        iSetColor(255, 249, 225), iFilledCircle(700, horizon_y1+70, 30, 300);
        iSetColor(255, 255, 250), iCircle(700, horizon_y1+70, 31, 300);
    }
}

void sort_cars(car c[], int size = 10){
    for(int i=0; i< size-1; i++){
        int index = i;
        for(int j=i+1; j<size; j++){
            if(c[index].car_z > c[j].car_z) index = j;
        }
        car temp = c[i]; c[i] = c[index], c[index] = temp;
    }
}