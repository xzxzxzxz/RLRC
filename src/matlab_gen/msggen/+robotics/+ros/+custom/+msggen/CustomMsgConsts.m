classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    properties (Constant)
        dbw_mkz_msgs_AmbientLight = 'dbw_mkz_msgs/AmbientLight'
        dbw_mkz_msgs_BrakeCmd = 'dbw_mkz_msgs/BrakeCmd'
        dbw_mkz_msgs_BrakeInfoReport = 'dbw_mkz_msgs/BrakeInfoReport'
        dbw_mkz_msgs_BrakeReport = 'dbw_mkz_msgs/BrakeReport'
        dbw_mkz_msgs_FuelLevelReport = 'dbw_mkz_msgs/FuelLevelReport'
        dbw_mkz_msgs_Gear = 'dbw_mkz_msgs/Gear'
        dbw_mkz_msgs_GearCmd = 'dbw_mkz_msgs/GearCmd'
        dbw_mkz_msgs_GearReject = 'dbw_mkz_msgs/GearReject'
        dbw_mkz_msgs_GearReport = 'dbw_mkz_msgs/GearReport'
        dbw_mkz_msgs_HillStartAssist = 'dbw_mkz_msgs/HillStartAssist'
        dbw_mkz_msgs_Misc1Report = 'dbw_mkz_msgs/Misc1Report'
        dbw_mkz_msgs_ParkingBrake = 'dbw_mkz_msgs/ParkingBrake'
        dbw_mkz_msgs_SteeringCmd = 'dbw_mkz_msgs/SteeringCmd'
        dbw_mkz_msgs_SteeringReport = 'dbw_mkz_msgs/SteeringReport'
        dbw_mkz_msgs_SurroundReport = 'dbw_mkz_msgs/SurroundReport'
        dbw_mkz_msgs_ThrottleCmd = 'dbw_mkz_msgs/ThrottleCmd'
        dbw_mkz_msgs_ThrottleInfoReport = 'dbw_mkz_msgs/ThrottleInfoReport'
        dbw_mkz_msgs_ThrottleReport = 'dbw_mkz_msgs/ThrottleReport'
        dbw_mkz_msgs_TirePressureReport = 'dbw_mkz_msgs/TirePressureReport'
        dbw_mkz_msgs_TurnSignal = 'dbw_mkz_msgs/TurnSignal'
        dbw_mkz_msgs_TurnSignalCmd = 'dbw_mkz_msgs/TurnSignalCmd'
        dbw_mkz_msgs_TwistCmd = 'dbw_mkz_msgs/TwistCmd'
        dbw_mkz_msgs_WatchdogCounter = 'dbw_mkz_msgs/WatchdogCounter'
        dbw_mkz_msgs_WheelPositionReport = 'dbw_mkz_msgs/WheelPositionReport'
        dbw_mkz_msgs_WheelSpeedReport = 'dbw_mkz_msgs/WheelSpeedReport'
        dbw_mkz_msgs_Wiper = 'dbw_mkz_msgs/Wiper'
        path_follower_Actuator = 'path_follower/Actuator'
        path_follower_ApplanixPose = 'path_follower/ApplanixPose'
        path_follower_ControllerTarget = 'path_follower/ControllerTarget'
        path_follower_SteeringCmd = 'path_follower/SteeringCmd'
        path_follower_SteeringCurrent = 'path_follower/SteeringCurrent'
        path_follower_Time = 'path_follower/Time'
        path_follower_Trajectory2D = 'path_follower/Trajectory2D'
        path_follower_TrajectoryPoint2D = 'path_follower/TrajectoryPoint2D'
        path_follower_TwistStamped = 'path_follower/TwistStamped'
        path_follower_Uout = 'path_follower/Uout'
        path_follower_dtlane = 'path_follower/dtlane'
        path_follower_state_Dynamic = 'path_follower/state_Dynamic'
        path_follower_traj_plan = 'path_follower/traj_plan'
        path_follower_waypoint = 'path_follower/waypoint'
    end
    
    methods (Static, Hidden)
        function messageList = getMessageList
            %getMessageList Generate a cell array with all message types.
            %   The list will be sorted alphabetically.
            
            persistent msgList
            if isempty(msgList)
                msgList = cell(40, 1);
                msgList{1} = 'dbw_mkz_msgs/AmbientLight';
                msgList{2} = 'dbw_mkz_msgs/BrakeCmd';
                msgList{3} = 'dbw_mkz_msgs/BrakeInfoReport';
                msgList{4} = 'dbw_mkz_msgs/BrakeReport';
                msgList{5} = 'dbw_mkz_msgs/FuelLevelReport';
                msgList{6} = 'dbw_mkz_msgs/Gear';
                msgList{7} = 'dbw_mkz_msgs/GearCmd';
                msgList{8} = 'dbw_mkz_msgs/GearReject';
                msgList{9} = 'dbw_mkz_msgs/GearReport';
                msgList{10} = 'dbw_mkz_msgs/HillStartAssist';
                msgList{11} = 'dbw_mkz_msgs/Misc1Report';
                msgList{12} = 'dbw_mkz_msgs/ParkingBrake';
                msgList{13} = 'dbw_mkz_msgs/SteeringCmd';
                msgList{14} = 'dbw_mkz_msgs/SteeringReport';
                msgList{15} = 'dbw_mkz_msgs/SurroundReport';
                msgList{16} = 'dbw_mkz_msgs/ThrottleCmd';
                msgList{17} = 'dbw_mkz_msgs/ThrottleInfoReport';
                msgList{18} = 'dbw_mkz_msgs/ThrottleReport';
                msgList{19} = 'dbw_mkz_msgs/TirePressureReport';
                msgList{20} = 'dbw_mkz_msgs/TurnSignal';
                msgList{21} = 'dbw_mkz_msgs/TurnSignalCmd';
                msgList{22} = 'dbw_mkz_msgs/TwistCmd';
                msgList{23} = 'dbw_mkz_msgs/WatchdogCounter';
                msgList{24} = 'dbw_mkz_msgs/WheelPositionReport';
                msgList{25} = 'dbw_mkz_msgs/WheelSpeedReport';
                msgList{26} = 'dbw_mkz_msgs/Wiper';
                msgList{27} = 'path_follower/Actuator';
                msgList{28} = 'path_follower/ApplanixPose';
                msgList{29} = 'path_follower/ControllerTarget';
                msgList{30} = 'path_follower/SteeringCmd';
                msgList{31} = 'path_follower/SteeringCurrent';
                msgList{32} = 'path_follower/Time';
                msgList{33} = 'path_follower/Trajectory2D';
                msgList{34} = 'path_follower/TrajectoryPoint2D';
                msgList{35} = 'path_follower/TwistStamped';
                msgList{36} = 'path_follower/Uout';
                msgList{37} = 'path_follower/dtlane';
                msgList{38} = 'path_follower/state_Dynamic';
                msgList{39} = 'path_follower/traj_plan';
                msgList{40} = 'path_follower/waypoint';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(0, 1);
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            serviceList = svcList;
        end
        
        function actionList = getActionList
            %getActionList Generate a cell array with all action types.
            %   The list will be sorted alphabetically.
            
            persistent actList
            if isempty(actList)
                actList = cell(0, 1);
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            actionList = actList;
        end
    end
end
