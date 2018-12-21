#ifndef ROOM_ROTATOR_H
#define ROOM_ROTATOR_H

#include <room_exploration/histogram.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include <geometry_msgs/Pose2D.h>


class RoomRotator
{
public:
        RoomRotator()
        {
        }

        void rotateRoom(const cv::Mat& room_map, cv::Mat& rotated_room_map, const cv::Mat& R, const cv::Rect& bounding_rect);

        // compute the affine rotation matrix for rotating a room into parallel alignment with x-axis (longer side of the room is aligned with x-axis)
        // R is the transform
        // bounding_rect is the ROI of the warped image
        // rotation_offset is an optional offset to the determined rotation, in [rad]
        // returns the computed optimal rotation angle, in [rad]
        double computeRoomRotationMatrix(const cv::Mat& room_map, cv::Mat& R, cv::Rect& bounding_rect, const double map_resolution,
                        const cv::Point* center=0, const double rotation_offset=0.);

        // computes the major direction of the walls from a map (preferably one room)
        // the map (room_map, CV_8UC1) is black (0) at impassable areas and white (255) on drivable areas
        double computeRoomMainDirection(const cv::Mat& room_map, const double map_resolution);

        // transforms a vector of points back to the original map and generates poses
        void transformPathBackToOriginalRotation(const std::vector<cv::Point2f>& fov_middlepoint_path, std::vector<geometry_msgs::Pose2D>& path_fov_poses, const cv::Mat& R);

        // converts a point path to a pose path with angles
        void transformPointPathToPosePath(const std::vector<cv::Point2f>& point_path, std::vector<geometry_msgs::Pose2D>& pose_path);

        // converts a point path to a pose path with angles, the points are already stored in pose_path
        void transformPointPathToPosePath(std::vector<geometry_msgs::Pose2D>& pose_path);

        // get min/max coordinates of free pixels (255)
        void getMinMaxCoordinates(const cv::Mat& map, cv::Point& min_room, cv::Point& max_room);
};





#endif // ROOM_ROTATOR_H
