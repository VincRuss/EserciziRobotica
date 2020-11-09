# include <ros/ros.h>
# include <pub_sub/encoder_readings.h>
# include <ctime>
# include <cstdlib>

int main (int argc, char **argv){
    // create node "publisher" on custom topic
    ros :: init(argc, argv, "publisher");
    ros :: NodeHandle nh;
    ros :: Publisher pub = nh.advertise<pub_sub :: encoder_readings>("encoder_topic", 1);

    // define loop rate (10Hz)
    ros :: Rate loopRate(10);

    // initialize message to be sent on previous topic
    pub_sub :: encoder_readings message;

    // set seed for pseudorandoms number generator
    srand (static_cast <unsigned> (time(0)));

    // utility initialization
    std :: vector<double> x (6);
    std :: vector<double> y (6);
    std :: vector<double> z (6);

    while (ros :: ok()){
        // generate random double number between 0.0 and 10.0
        for(int i = 0; i < 6; i++){
            x [i] = static_cast <double> (rand()) / static_cast <float> (RAND_MAX) * 10.0;
            y [i] = static_cast <double> (rand()) / static_cast <float> (RAND_MAX) * 10.0;
            z [i] = static_cast <double> (rand()) / static_cast <float> (RAND_MAX) * 10.0;
        }

        // populate fields of message
        message.position_x = x;
        message.position_y = y;
        message.position_z = z;

        // publish message on custom topic
        pub.publish(message);

        ros :: spinOnce();

        loopRate.sleep();
    }

    return 0;
}