#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ocean.h"
#include "octorok.h"
#include "rock.h"
#include "canonball.h"
#include "heart.h"
#include "booster.h"
#include "barrel.h"
#include "ganondorf.h"
#include "triforce.h"
#include "island.h"
#include "link.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball player;

Island island;
int at_island = 0;

Link link;
int create_link = 0;
int link_block = 0;

Ganondorf ganon;
int ganon_attack_flag = 0;
int mega_block = 0;
int end_tick = 0;
int segment_no = 0;

Ocean ocean;

CanonBall canon[10];
CanonBall ganon_canon[120];
int canon_timer = 0; //Player canon delay
int canon_shot = 0; //Whether a canon was shot or not
int canon_count = 0; //Number of active canonballs

int ganon_canon_timer = 0; //Player canon delay
int ganon_canon_shot = 0; //Whether a canon was shot or not
int ganon_canon_count = 0; //Number of active canonballs

Heart heart[10];
int heart_count = 10;
int hearts = 3;
int blink_flag = 0;
char heartString[100];
int invin_flag = 0;
int invin_timer = 0;

float wind_x = 0;
float wind_z = 0;
int wind_tick = 0;
int wind_flag = 0;

Octorok octorok[20];
int enemy_count = 20;

float y_old;
float xz_old;

Triforce triforce[3];
float pos_x;
float pos_z;

Rock rock[20];
int rock_count = 20;
int rock_collision_flag = 0;
int block = 0;

Barrel barrel[20];
int barrel_count = 20;

Booster booster[5];
int booster_count = 2;

enum camera{BOAT_VIEW, TOWER_VIEW, TOP_VIEW, FOLLOW_VIEW, HELICOPTER_VIEW};
enum camera cam_view = TOWER_VIEW;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, scr_zoo =20;
float xz_plane_angle = 80, y_angle = 30;
int ortho = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    glm::vec3 eye = glm::vec3 (20*cos(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f), 20*sin(y_angle*M_PI/180.0f), 20*sin(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f));
    glm::vec3 target = player.position;
    glm::vec3 dir = player.direction;
    glm::vec3 pos =player.position;
    if(at_island){
          target = link.position;
           dir = link.direction;
             pos = link.position;
    }

    glm::vec3 up = glm::vec3(0, 1, 0);

    if (cam_view == BOAT_VIEW){
          eye = target + 5.0f * dir + glm::vec3(0,10,0);
          target = eye + dir;
      }
      else if (cam_view == TOP_VIEW){
          eye = target + glm::vec3(0, 20, 0);
          up = glm::vec3(0,0,-1);
      }
      else if (cam_view == TOWER_VIEW){
          eye = glm::vec3(0, 30, 20);
          target = glm::vec3(0,0,0);
      }
      else if (cam_view == HELICOPTER_VIEW){
        if(!ortho)
          eye = pos + glm::vec3 ( scr_zoo*cos(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f), scr_zoo*sin(y_angle*M_PI/180.0f), scr_zoo*sin(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f) );
        else
            eye = pos + glm::vec3 ( 200*cos(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f), 20*sin(y_angle*M_PI/180.0f), 20*sin(xz_plane_angle*M_PI/180.0f)*cos(y_angle*M_PI/180.0f) );
    }
    else if (cam_view == FOLLOW_VIEW){
        eye = pos - 30.0f*dir + glm::vec3(0, 50, 0);
    }

      // Compute Camera matrix (view)
      Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
      glm::mat4 VP = Matrices.projection * Matrices.view;
      glm::mat4 MVP;  // MVP = Projection * View * Model

    for(int i = 0;i<enemy_count;i++)
        octorok[i].draw(VP);
    for(int i = 0;i<rock_count;i++)
        rock[i].draw(VP);
    for(int i = 0;i<heart_count;i++)
        heart[i].draw(VP);
    for(int i = 0;i<booster_count;i++)
       booster[i].draw(VP);
    for(int i = 0;i<canon_count;i++)
        canon[i].draw(VP);
    for(int i = 0;i<ganon_canon_count;i++)
        ganon_canon[i].draw(VP);
    for(int i = 0;i<barrel_count;i++)
        barrel[i].draw(VP);
    for(int i = 0;i<3;i++)
        triforce[i].draw(VP);
    if(at_island) link.draw(VP);
    island.draw(VP);
    ganon.draw(VP);
    ocean.draw(VP);
     if(not blink_flag && !at_island) player.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int W = glfwGetKey(window, GLFW_KEY_W);
    int A = glfwGetKey(window, GLFW_KEY_A);
    int S = glfwGetKey(window, GLFW_KEY_S);
    int D = glfwGetKey(window, GLFW_KEY_D);
    int Y = glfwGetKey(window, GLFW_KEY_Y);
    int T = glfwGetKey(window, GLFW_KEY_T);
    int F = glfwGetKey(window, GLFW_KEY_F);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int boat = glfwGetKey(window, GLFW_KEY_1);
    int top = glfwGetKey(window, GLFW_KEY_3);
    int tower = glfwGetKey(window, GLFW_KEY_2);
    int follow = glfwGetKey(window, GLFW_KEY_4);
    int helicopter = glfwGetKey(window, GLFW_KEY_5);
    int shoot_canon = glfwGetKey(window, GLFW_KEY_E);
    int camera_left  = glfwGetKey(window, GLFW_KEY_LEFT);
     int camera_right = glfwGetKey(window, GLFW_KEY_RIGHT);
     int camera_up = glfwGetKey(window, GLFW_KEY_UP);
     int camera_down = glfwGetKey(window, GLFW_KEY_DOWN);


      if (camera_left && cam_view == HELICOPTER_VIEW) {
          xz_plane_angle--;
      }
      else if (camera_right && cam_view == HELICOPTER_VIEW){
          xz_plane_angle++;
      }
      else if (camera_up && cam_view == HELICOPTER_VIEW){
          if(y_angle >4 )
          y_angle -= 2;
      }
      else if (camera_down && cam_view == HELICOPTER_VIEW){
           if(y_angle <=85)
          y_angle += 2;
      }

    if(Y){
        ortho = 0;
        reset_screen();
    }
    if(F && player.booster_count > 0){
        player.booster_count --;
        player.booster_time = 120;

    }
    if(T){
        ortho = 1;
        reset_screen();
    }
    if(!rock_collision_flag && !at_island){
    if(W && !block){
        player.speedx = player.direction.x;
        player.speedz = player.direction.z;    }
    if(A&& !block){
          player.rotation += 2;
    }
    if(S&& !block){
        player.speedx = -player.direction.x;
        player.speedz = -player.direction.z;
    }
    if(D&& !block){
        player.rotation -= 2;
    }

    if(jump && player.flag_air == 0){
        player.speedy = 1.5;
        player.position.y += 0.02;
        player.flag_air = 1;
    }
    }
    if(shoot_canon &&  canon_shot != 1){
        canon_shot = 1;
        canon[canon_count] = CanonBall(player.position.x,player.position.y,player.position.z);
        canon[canon_count].direction = player.direction;
        canon[canon_count].initx = player.position.x;
        canon[canon_count].initz = player.position.z;
        canon_count ++;
    }


    if(top) cam_view = TOP_VIEW;
    else if(tower) cam_view = TOWER_VIEW;
    else if (boat) cam_view = BOAT_VIEW;
    else if(helicopter) cam_view = HELICOPTER_VIEW;
    else if(follow) cam_view = FOLLOW_VIEW;

}

void tick_elements() {
    player.tick();

    if(player.booster_time > 0) player.booster_time --;

    //End Game Dialog
    if(mega_block) {
        end_tick ++;
    if(end_tick >= 120){
        segment_no ++;
        end_tick = 0;
    }
    if(segment_no == 1){
        glfwSetWindowTitle(window,"You have fulfiled the prophecy of the Hero of Time");
    }
    else if(segment_no == 2){
        quit(window);
    }
    }

    if(canon_shot){
        canon_timer ++;
        if(canon_timer >= 60){
            canon_shot = 0;
            canon_timer = 0;
        }
    }


    //Canon tick inc
    for(int i=0;i<canon_count;i++){
        canon[i].rotation += 60;
        if(canon[i].tick_time > 180){
            for(int j=i;j<canon_count-1;j++){
                canon[j] = canon[j+1];
            }
            canon_count --;
        }
        canon[i].inc += 0.4;
    }



    wind_tick ++;
    if(wind_tick >= 120) wind_tick = 0;


    //Rock Collision   
    block = 0;
    for(int i = 0;i<rock_count;i++){
    if(detect_collision(player.bounding_box(), rock[i].bounding_box())){
        float tempx = player.position.x;
        float tempz = player.position.z;
        if(!invin_flag){
            hearts -= 1;
            invin_flag = 1;
            blink_flag = 0 ;
        }
        player.position.x = tempx - 0.2;
        player.position.z = tempz - 0.2;
        player.speedx = -player.speedx;
        player.speedz = -player.speedz;
        block = 1;
    }
    }

    //Triforce all collect
    if(player.triforce_count == 3){
        ganon_attack_flag = 1;
    }

    //Ganon Canon tick inc
    for(int i=0;i<ganon_canon_count;i++){
        ganon_canon[i].tick_time++;
        if(ganon_canon[i].tick_time > 240){
            for(int j=i;j<ganon_canon_count-1;j++){
                ganon_canon[j] = ganon_canon[j+1];
            }
            ganon_canon_count --;
        }
        ganon_canon[i].inc += 0.4;
    }

    //Ganon canon's damage to player
    for(int i=0;i<ganon_canon_count;i++){
        if(detect_collision(player.bounding_box(), ganon_canon[i].bounding_box())){
             hearts  --;
        }
    }

    //Ganon shoots canon
    if(detect_collision(player.bounding_box(), ganon.bounding_box())){
        //Rotate Ganon
        if(ganon.health >= 3)
        ganon.rotation += 1;
        else
            ganon.rotation += 2;

        ganon.tick();

        //Fire canon in all directions
        if(ganon_canon_count<120){
        ganon_canon[ganon_canon_count] = CanonBall(0,1,200);
        ganon_canon[ganon_canon_count].direction = ganon.direction;
        ganon_canon[ganon_canon_count].initx = 0;
        ganon_canon[ganon_canon_count].initz = 200;
        ganon_canon_count ++;
        }

       // cout << ganon_canon[0].position.z <<"s ";
    if(detect_collision(player.bounding_box(), ganon.bounding_box_2())){
               float tempx = player.position.x;
               float tempz = player.position.z;
               if(!invin_flag){
                   hearts -= 1;
                   invin_flag = 1;
                   blink_flag = 0 ;
               }
               player.position.x = tempx - 0.2;
               player.position.z = tempz - 0.2;
               player.speedx = -player.speedx;
               player.speedz = -player.speedz;
               block = 1;
           }
    }

    //Ganon Canon fire against player
    for(int i = 0;i<ganon_canon_count;i++){
        ganon_canon[i].tick();
    }

    //Attacking Ganon with players canon
    for(int i=0;i<canon_count;i++){
        if(player.triforce_count == 3){
        if(detect_collision(ganon.bounding_box(), canon[i].bounding_box())){
            ganon.health --;
            for(int j=i;j<canon_count-1;j++){
                canon[j] = canon[j+1];
            }
             canon_count --;
        }
        }
    }

    //Defeated Ganon
     if(ganon.health == 0){
               ganon = Ganondorf(0,-10000,0);
         glfwSetWindowTitle(window,"You Defeated Ganondorf and saved the kingdom of Hyrule");
         mega_block = 1;
     }

    //Canonball collision with octorok
    for(int i=0;i<canon_count;i++){
        for(int j=0;j<enemy_count;j++){
        if(detect_collision(octorok[j].bounding_box_2(), canon[i].bounding_box())){
            octorok[j].position = glm::vec3 (rand()%300-150,0 ,rand()%300-150);
            octorok[j].starting_point_x=octorok[j].position.x;
            octorok[j].starting_point_z=octorok[j].position.z;
            for(int j=i;j<canon_count-1;j++){
                canon[j] = canon[j+1];
            }
             canon_count --;
        }
        }
    }

    //Booster Collision
    for(int i = 0;i<booster_count;i++){
        booster[i].rotation += 2;
    if(detect_collision(player.bounding_box(), booster[i].bounding_box())){
        booster[i].position.x = 10000000000;
        booster[i].position.z = 10000000000;
        player.booster_count ++;
    }
    }


    //Invincibility after hit
    if(invin_flag){
        invin_timer ++;
        blink_flag = !blink_flag;
        if(invin_timer >= 200){
            invin_flag = 0;
            invin_timer = 0;
        }
    }

    //End of Game
    if(hearts <= 0){
    quit(window);
    }


    //Move Enemy
    for(int i = 0;i<enemy_count;i++){
     if(i%2 == 1){
         if( octorok[i].position.x - octorok[i].starting_point_x >=2 ){
            octorok[i].dir_flag = 0;
         }
         else if(octorok[i].position.x - octorok[i].starting_point_x <= -2){
            octorok[i].dir_flag = 1;
         }
         if(octorok[i].dir_flag) octorok[i].position.x += 0.1;
         else octorok[i].position.x -= 0.1;
     }
     else if (i%2 == 0) {
         if( octorok[i].position.z - octorok[i].starting_point_z >=2 ){
            octorok[i].dir_flag = 0;
         }
         else if(octorok[i].position.z - octorok[i].starting_point_z <= -2){
            octorok[i].dir_flag = 1;
         }
         if(octorok[i].dir_flag) octorok[i].position.z += 0.1;
         else octorok[i].position.z -= 0.1;
     }
    }
    //Wind Randomization
    if(wind_tick <= 0){
        wind_x = ((rand()%200)-100)/100000.0;
        wind_z = ((rand()%200)-100)/100000.0;
    }

    //Wind Effect
    player.speedx += wind_x;
    player.speedz += wind_z;

    //Heart Gain Health
    for(int i = 0;i<heart_count;i++){
       heart[i].rotation +=2;
    if(detect_collision(player.bounding_box(), heart[i].bounding_box())){
        heart[i].position.x = 10000000000;
        heart[i].position.z = 10000000000;
        hearts += 1;
    }
    }

    //Octorok collision detector
    for(int i = 0;i<enemy_count;i++){
        if(detect_collision(player.bounding_box(), octorok[i].bounding_box())){
            if(detect_collision(player.bounding_box(), octorok[i].bounding_box_2())){
                if(!invin_flag){
                    hearts -= 1;
                    invin_flag = 1;
                    blink_flag = 0 ;
                }
            }
        }
    }

    //Island Drop off
    if(detect_collision(player.bounding_box(),island.bounding_box())){
        float tempx = player.position.x;
        float tempz = player.position.z;

        player.speedx = 0;
        player.speedz = 0;
        block = 1;
        if(!at_island) create_link = 1;
        at_island = 1;

    }
    else at_island = 0;

    //Make Link
    if(create_link){
        link         = Link(player.position.x,1,player.position.z);
        create_link = 0;
    }


    //At island get down
    if(at_island){
    if(detect_collision(link.bounding_box(),island.bounding_box())){
        int W = glfwGetKey(window, GLFW_KEY_W);
        int A = glfwGetKey(window, GLFW_KEY_A);
        int S = glfwGetKey(window, GLFW_KEY_S);
        int D = glfwGetKey(window, GLFW_KEY_D);
        int J = glfwGetKey(window, GLFW_KEY_SPACE);

            if(W && !link_block){
                   link.speedx = link.direction.x;
                   link.speedz = link.direction.z;    }
               if(A&& !link_block){
                     link.rotation += 2;
               }
               if(S&& !link_block){
                   link.speedx = -link.direction.x;
                   link.speedz = -link.direction.z;
               }
               if(D&& !link_block){
                   link.rotation -= 2;
               }

               if(J && link.flag_air == 0){
                   link.speedy = 1.5;
                   link.position.y += 0.02;
                   link.flag_air = 1;
               }

    link.tick();
    }else{
        if(at_island){
            player.position.x = link.position.x;
             player.position.z = link.position.z;
        }
        at_island = 0;
    }
    }


    //Barrel check
    for(int i = 0;i<barrel_count;i++){
    if(detect_collision(player.bounding_box(), barrel[i].bounding_box())){
        float tempx = player.position.x;
        float tempz = player.position.z;

        player.position.x = tempx - 0.2;
        player.position.z = tempz - 0.2;
        player.speedx = -player.speedx;
        player.speedz = -player.speedz;
        block = 1;
    }

    else{
        //Triforce Collect
        for(int i = 0;i<3;i++){
        if(detect_collision(player.bounding_box(), triforce[i].bounding_box())){
            triforce[i].position.x = 10000000000;
            triforce[i].position.z = 10000000000;
            player.triforce_count ++;
        }
        }
    }
    }

    //Canon fire of player
    for(int i = 0;i<canon_count;i++){
        canon[i].tick();
    }

    //Heart Counter Display
    sprintf (heartString,"Hearts : %d",hearts);
    if(!mega_block)
    glfwSetWindowTitle(window,heartString);

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player      = Ball(0, 0, COLOR_RED);
    ocean       = Ocean(0,0);
    island      = Island(-300,0,-300);


     for(int i = 0;i<enemy_count;i++)
         octorok[i] = Octorok(rand()%300-150,0 ,rand()%300-150);
     for(int i = 0;i<rock_count;i++)
        rock[i] = Rock(rand()%300-150, 0 ,rand()%300-150);

     for(int i = 0;i<barrel_count;i++){
        pos_x = rand()%300-150;
        pos_z = rand()%300-150;
        if(i < 3) triforce[i] = Triforce(pos_x, 3 ,pos_z);
        if(i>=3 && i<3+booster_count) booster[i-3] = Booster(pos_x, 4 ,pos_z);
        if(i>=3+booster_count && i<3+booster_count+heart_count) heart[i-(3+booster_count)] = Heart(pos_x, 4 ,pos_z);

        barrel[i] = Barrel(pos_x, 0 ,pos_z);
    }
     ganon = Ganondorf(0,0,200);


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1920;
    int height = 1080;

    window = initGLFW(width, height);

    initGL (window, width, height);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
            (abs(a.z - b.z) * 2 < (a.length + b.length));
}
//For 1920*1080 screens only, Won't work properly on 720p screens
void move_cursor(double x,double y){
if (cam_view == HELICOPTER_VIEW){
double temp = sinh(x/y) * 180 / 3.1415;
while(temp > 360.00) {
    temp -= 360.00;
}
while(temp < -360.00) {
    temp += 360.00;
}
//cout << temp << " ";
if(x < xz_old) player.rotation += 1;
else if(x > xz_old)player.rotation -= 1;
if(y < y_old) player.rotation += 0.5;
else if(y > y_old)player.rotation -= 0.5;
xz_old = x;
y_old = y;
//if(y_angle > y_old) player.rotation += 3;
//else if(y_angle > y_old) player.rotation += 3;
xz_plane_angle = x/10.00;
y_angle = y/10.00;
}
}

void reset_screen() {
    float top    = screen_center_y + 18 / screen_zoom;
    float bottom = screen_center_y - 18 / screen_zoom;
    float left   = screen_center_x - 32 / screen_zoom;
    float right  = screen_center_x + 32 / screen_zoom;
    if(ortho)Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    else Matrices.projection = glm::perspective(90.0f, 16/9.0f, 0.01f, 500.0f);
}
