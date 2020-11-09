# include <ros/ros.h>
# include <pub_sub/encoder_readings.h>

// function for handling messages on topic of intrest
void manageReadings(const pub_sub :: encoder_readings& msg){
    // extract message's fields
    std::vector<double> x = msg.position_x;
    std::vector<double> y = msg.position_y;
    std::vector<double> z = msg.position_z;

    // if it contains expected number of readings, print them
    int len=x.size();
    if (len == y.size() && len == z.size()){
        for (int i=0; i<len; i++)
            ROS_INFO_STREAM("Joint " << i+1 << ": x = " << x[i] << ", y = " << y[i] << ", z = " << z[i]);
    }
    // report error
    else
        ROS_ERROR_STREAM("Received less joints positions than expected");

    // print for better formatting of the output
    std :: cout << "\n";
}

int main (int argc, char **argv){
    // create node subscriber on custom topic
    ros :: init(argc, argv, "subscriber");
    ros :: NodeHandle nh;
    ros :: Subscriber sub = nh.subscribe("encoder_topic", 1, manageReadings);

    ros :: spin();

    return 0;
}