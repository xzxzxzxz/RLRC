classdef Actuator < robotics.ros.Message
    %Actuator MATLAB implementation of path_follower/Actuator
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'path_follower/Actuator' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '8164b580b4ff14b976d32e45c6c9f9d9' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant)
        DIRECTIONFORWARD = uint8(0)
        DIRECTIONREVERSE = uint8(1)
        ANGLECONTROL = uint8(0)
        TORQUECONTROL = uint8(1)
    end
    
    properties (Constant, Access = protected)
        StdMsgsHeaderClass = robotics.ros.msg.internal.MessageFactory.getClassForType('std_msgs/Header') % Dispatch to MATLAB class for message type std_msgs/Header
    end
    
    properties (Dependent)
        Header
        Direction
        SteeringMode
        SteeringValue
        BrakePressure
        ThrottleFraction
        Timestamp
    end
    
    properties (Access = protected)
        Cache = struct('Header', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'BrakePressure', 'Direction', 'Header', 'SteeringMode', 'SteeringValue', 'ThrottleFraction', 'Timestamp'} % List of non-constant message properties
        ROSPropertyList = {'brake_pressure', 'direction', 'header', 'steering_mode', 'steering_value', 'throttle_fraction', 'timestamp'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = Actuator(msg)
            %Actuator Construct the message object Actuator
            import com.mathworks.toolbox.robotics.ros.message.MessageInfo;
            
            % Support default constructor
            if nargin == 0
                obj.JavaMessage = obj.createNewJavaMessage;
                return;
            end
            
            % Construct appropriate empty array
            if isempty(msg)
                obj = obj.empty(0,1);
                return;
            end
            
            % Make scalar construction fast
            if isscalar(msg)
                % Check for correct input class
                if ~MessageInfo.compareTypes(msg(1), obj.MessageType)
                    error(message('robotics:ros:message:NoTypeMatch', obj.MessageType, ...
                        char(MessageInfo.getType(msg(1))) ));
                end
                obj.JavaMessage = msg(1);
                return;
            end
            
            % Check that this is a vector of scalar messages. Since this
            % is an object array, use arrayfun to verify.
            if ~all(arrayfun(@isscalar, msg))
                error(message('robotics:ros:message:MessageArraySizeError'));
            end
            
            % Check that all messages in the array have the correct type
            if ~all(arrayfun(@(x) MessageInfo.compareTypes(x, obj.MessageType), msg))
                error(message('robotics:ros:message:NoTypeMatchArray', obj.MessageType));
            end
            
            % Construct array of objects if necessary
            objType = class(obj);
            for i = 1:length(msg)
                obj(i,1) = feval(objType, msg(i)); %#ok<AGROW>
            end
        end
        
        function header = get.Header(obj)
            %get.Header Get the value for property Header
            if isempty(obj.Cache.Header)
                obj.Cache.Header = feval(obj.StdMsgsHeaderClass, obj.JavaMessage.getHeader);
            end
            header = obj.Cache.Header;
        end
        
        function set.Header(obj, header)
            %set.Header Set the value for property Header
            validateattributes(header, {obj.StdMsgsHeaderClass}, {'nonempty', 'scalar'}, 'Actuator', 'Header');
            
            obj.JavaMessage.setHeader(header.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Header)
                obj.Cache.Header.setJavaObject(header.getJavaObject);
            end
        end
        
        function direction = get.Direction(obj)
            %get.Direction Get the value for property Direction
            direction = typecast(int8(obj.JavaMessage.getDirection), 'uint8');
        end
        
        function set.Direction(obj, direction)
            %set.Direction Set the value for property Direction
            validateattributes(direction, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'Direction');
            
            obj.JavaMessage.setDirection(direction);
        end
        
        function steeringmode = get.SteeringMode(obj)
            %get.SteeringMode Get the value for property SteeringMode
            steeringmode = typecast(int8(obj.JavaMessage.getSteeringMode), 'uint8');
        end
        
        function set.SteeringMode(obj, steeringmode)
            %set.SteeringMode Set the value for property SteeringMode
            validateattributes(steeringmode, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'SteeringMode');
            
            obj.JavaMessage.setSteeringMode(steeringmode);
        end
        
        function steeringvalue = get.SteeringValue(obj)
            %get.SteeringValue Get the value for property SteeringValue
            steeringvalue = double(obj.JavaMessage.getSteeringValue);
        end
        
        function set.SteeringValue(obj, steeringvalue)
            %set.SteeringValue Set the value for property SteeringValue
            validateattributes(steeringvalue, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'SteeringValue');
            
            obj.JavaMessage.setSteeringValue(steeringvalue);
        end
        
        function brakepressure = get.BrakePressure(obj)
            %get.BrakePressure Get the value for property BrakePressure
            brakepressure = double(obj.JavaMessage.getBrakePressure);
        end
        
        function set.BrakePressure(obj, brakepressure)
            %set.BrakePressure Set the value for property BrakePressure
            validateattributes(brakepressure, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'BrakePressure');
            
            obj.JavaMessage.setBrakePressure(brakepressure);
        end
        
        function throttlefraction = get.ThrottleFraction(obj)
            %get.ThrottleFraction Get the value for property ThrottleFraction
            throttlefraction = double(obj.JavaMessage.getThrottleFraction);
        end
        
        function set.ThrottleFraction(obj, throttlefraction)
            %set.ThrottleFraction Set the value for property ThrottleFraction
            validateattributes(throttlefraction, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'ThrottleFraction');
            
            obj.JavaMessage.setThrottleFraction(throttlefraction);
        end
        
        function timestamp = get.Timestamp(obj)
            %get.Timestamp Get the value for property Timestamp
            timestamp = double(obj.JavaMessage.getTimestamp);
        end
        
        function set.Timestamp(obj, timestamp)
            %set.Timestamp Set the value for property Timestamp
            validateattributes(timestamp, {'numeric'}, {'nonempty', 'scalar'}, 'Actuator', 'Timestamp');
            
            obj.JavaMessage.setTimestamp(timestamp);
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.Header = [];
        end
        
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Clear any existing cached properties
            cpObj.resetCache;
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Direction = obj.Direction;
            cpObj.SteeringMode = obj.SteeringMode;
            cpObj.SteeringValue = obj.SteeringValue;
            cpObj.BrakePressure = obj.BrakePressure;
            cpObj.ThrottleFraction = obj.ThrottleFraction;
            cpObj.Timestamp = obj.Timestamp;
            
            % Recursively copy compound properties
            cpObj.Header = copy(obj.Header);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Direction = strObj.Direction;
            obj.SteeringMode = strObj.SteeringMode;
            obj.SteeringValue = strObj.SteeringValue;
            obj.BrakePressure = strObj.BrakePressure;
            obj.ThrottleFraction = strObj.ThrottleFraction;
            obj.Timestamp = strObj.Timestamp;
            obj.Header = feval([obj.StdMsgsHeaderClass '.loadobj'], strObj.Header);
        end
    end
    
    methods (Access = ?robotics.ros.Message)
        function strObj = saveobj(obj)
            %saveobj Implements saving of message to MAT file
            
            % Return an empty element if object array is empty
            if isempty(obj)
                strObj = struct.empty;
                return
            end
            
            strObj.Direction = obj.Direction;
            strObj.SteeringMode = obj.SteeringMode;
            strObj.SteeringValue = obj.SteeringValue;
            strObj.BrakePressure = obj.BrakePressure;
            strObj.ThrottleFraction = obj.ThrottleFraction;
            strObj.Timestamp = obj.Timestamp;
            strObj.Header = saveobj(obj.Header);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.path_follower.Actuator.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.path_follower.Actuator;
            obj.reload(strObj);
        end
    end
end