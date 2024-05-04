// typedef struct car{
//     double car_dy = 120, car_dx = 400, car_x = 715, car_y = 50, car_z = 300;
//     int color[3] = {10, 100, 256}; int x;
//     double velocity = 1, acceleration = 0;
// } car;

// if(c.car_z > 0 && c.car_z<= depth+100){
//         double z = depth - c.car_z;
//         double y_for_drawing = sqrt((depth*depth*horizon_y1*horizon_y1-(z-depth)*(z-depth)*horizon_y1*horizon_y1)/(depth*depth)), x_for_drawing = (715 - c.car_x)*(y_for_drawing-horizon_y1)/horizon_y1+715;
//         double car_top[2][4] = {{x_for_drawing, x_for_drawing+c.car_dx*d_dz*c.car_z, x_for_drawing+(c.car_dx-99)*d_dz*c.car_z,x_for_drawing+99*d_dz*c.car_z},{y_for_drawing+c.car_dy*d_dz*c.car_z, y_for_drawing+c.car_dy*d_dz*c.car_z, y_for_drawing+(c.car_dy+50)*d_dz*c.car_z, y_for_drawing+(c.car_dy+50)*d_dz*c.car_z}};
//         double hood[2][4] = {{x_for_drawing+(c.car_dx-59)*d_dz*c.car_z, x_for_drawing+59*d_dz*c.car_z, x_for_drawing+84*d_dz*c.car_z, x_for_drawing+(c.car_dx-84)*d_dz*c.car_z}, {y_for_drawing+c.car_dy*d_dz*c.car_z, y_for_drawing+c.car_dy*d_dz*c.car_z, y_for_drawing+(c.car_dy+110)*d_dz*c.car_z, y_for_drawing+(c.car_dy+110)*d_dz*c.car_z}};
//         double lights[2][3] = {{x_for_drawing+20*d_dz*c.car_z, y_for_drawing+50*d_dz*c.car_z, 15*d_dz*c.car_z},{car_top[0][1]-20*d_dz*c.car_z, y_for_drawing+50*d_dz*c.car_z, 15*d_dz*c.car_z}};
//         double wheels[2][4] = {{x_for_drawing, y_for_drawing-80*c.car_z*d_dz, 80*d_dz*c.car_z, 80*d_dz*c.car_z}, {car_top[0][1]-80*d_dz*c.car_z, y_for_drawing-80*d_dz*c.car_z, 80*d_dz*c.car_z, 80*d_dz*c.car_z}};
//         //drawing car body
//         iSetColor(230, 120, 100);
//         iFilledRectangle(x_for_drawing, y_for_drawing, c.car_dx*d_dz*c.car_z, c.car_dy*d_dz*c.car_z);
//         //drawing car top
//         iSetColor(256, 256, 256);
//         iFilledPolygon(car_top[0], car_top[1],4);
//         //drawing car hood
//         iSetColor(80, 200, 220);
//         iFilledPolygon(hood[0], hood[1], 4);
//         iSetColor(0,0,0);
//         iPolygon(hood[0], hood[1], 4);
//         //drawing car back lights
//         iSetColor(0,0,0);
//         iCircle(lights[0][0], lights[0][1], lights[0][2]);
//         iCircle(lights[1][0], lights[1][1], lights[1][2]);
//         iSetColor(250,0,0);
//         iFilledCircle(lights[0][0], lights[0][1], lights[0][2]);
//         iFilledCircle(lights[1][0], lights[1][1], lights[1][2]);
//         //drawing car wheels
//         iSetColor(0, 0, 0);
//         iFilledRectangle(wheels[0][0], wheels[0][1], wheels[0][2], wheels[0][3]);
//         iFilledRectangle(wheels[1][0], wheels[1][1], wheels[1][2], wheels[1][3]);
//     }
// double railing_top[2][3][3] = {{{road_x[0], road_x[5], road_x[5]},{road_y[0], railing[0][1][2], railing[0][1][2]+50}},{{road_x[1], road_x[2], road_x[2]},{road_y[1], railing[1][1][2], railing[1][1][2]+50}}};
//     // //railing top
//     // iSetColor(240, 152, 64);
//     // iFilledPolygon(railing_top[0][0], railing_top[0][1], 3);
//     // iFilledPolygon(railing_top[1][0], railing_top[1][1], 3);
//     // iSetColor(0, 0, 0);
//     // iLine(railing[0][0][0], railing[0][1][0], railing[0][0][2], railing[0][1][2]);
//     // iLine(railing[1][0][0], railing[1][1][0], railing[1][0][2], railing[1][1][2]);
//     // iLine(railing[0][0][0], railing[0][1][0], railing_top[0][0][2], railing_top[0][1][2]);
//     // iLine(railing[1][0][0], railing[1][1][0], railing_top[1][0][2], railing_top[1][1][2]);

// //draw pyramids
    // iSetColor(225, 173, 84);
    // double pyramid[2][4]={{200, 225, 250, 225},{horizon_y1, horizon_y1-10, horizon_y1, horizon_y1+20}};
    // double pyramid_border[2][2][3] = {{{pyramid[0][0], pyramid[0][1], pyramid[0][3]},{pyramid[1][0], pyramid[1][1], pyramid[1][3]}}, 
    //                                   {{pyramid[0][1], pyramid[0][2], pyramid[0][3]},{pyramid[1][1], pyramid[1][2], pyramid[1][3]}}};
    // iFilledPolygon(pyramid[0], pyramid[1], 4);
    // iSetColor(105, 72, 16);
    // iPolygon(pyramid_border[0][0], pyramid_border[0][1], 3); iPolygon(pyramid_border[1][0], pyramid_border[1][1], 3);
