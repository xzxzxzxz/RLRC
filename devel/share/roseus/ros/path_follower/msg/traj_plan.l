;; Auto-generated. Do not edit!


(when (boundp 'path_follower::traj_plan)
  (if (not (find-package "PATH_FOLLOWER"))
    (make-package "PATH_FOLLOWER"))
  (shadow 'traj_plan (find-package "PATH_FOLLOWER")))
(unless (find-package "PATH_FOLLOWER::TRAJ_PLAN")
  (make-package "PATH_FOLLOWER::TRAJ_PLAN"))

(in-package "ROS")
;;//! \htmlinclude traj_plan.msg.html


(defclass path_follower::traj_plan
  :super ros::object
  :slots (_j _i _x _y _theta _v _rate_yaw ))

(defmethod path_follower::traj_plan
  (:init
   (&key
    ((:j __j) 0)
    ((:i __i) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:theta __theta) 0.0)
    ((:v __v) 0.0)
    ((:rate_yaw __rate_yaw) 0.0)
    )
   (send-super :init)
   (setq _j (round __j))
   (setq _i (round __i))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _theta (float __theta))
   (setq _v (float __v))
   (setq _rate_yaw (float __rate_yaw))
   self)
  (:j
   (&optional __j)
   (if __j (setq _j __j)) _j)
  (:i
   (&optional __i)
   (if __i (setq _i __i)) _i)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:rate_yaw
   (&optional __rate_yaw)
   (if __rate_yaw (setq _rate_yaw __rate_yaw)) _rate_yaw)
  (:serialization-length
   ()
   (+
    ;; int32 _j
    4
    ;; int32 _i
    4
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _theta
    8
    ;; float64 _v
    8
    ;; float64 _rate_yaw
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _j
       (write-long _j s)
     ;; int32 _i
       (write-long _i s)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _v
       (sys::poke _v (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rate_yaw
       (sys::poke _rate_yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _j
     (setq _j (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _i
     (setq _i (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _v
     (setq _v (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rate_yaw
     (setq _rate_yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get path_follower::traj_plan :md5sum-) "f8c2ada89420e3e8b85c22cafba5a2f5")
(setf (get path_follower::traj_plan :datatype-) "path_follower/traj_plan")
(setf (get path_follower::traj_plan :definition-)
      "int32 j
int32 i
float64 x
float64 y
float64 theta
float64 v
float64 rate_yaw


")



(provide :path_follower/traj_plan "f8c2ada89420e3e8b85c22cafba5a2f5")


