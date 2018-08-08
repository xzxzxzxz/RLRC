classdef Wiper < robotics.ros.Message
    %Wiper MATLAB implementation of dbw_mkz_msgs/Wiper
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'dbw_mkz_msgs/Wiper' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '7fccb48d5d1df108afaa89f8fc14ce1c' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant)
        OFF = uint8(0)
        AUTOOFF = uint8(1)
        OFFMOVING = uint8(2)
        MANUALOFF = uint8(3)
        MANUALON = uint8(4)
        MANUALLOW = uint8(5)
        MANUALHIGH = uint8(6)
        MISTFLICK = uint8(7)
        WASH = uint8(8)
        AUTOLOW = uint8(9)
        AUTOHIGH = uint8(10)
        COURTESYWIPE = uint8(11)
        AUTOADJUST = uint8(12)
        RESERVED = uint8(13)
        STALLED = uint8(14)
        NODATA = uint8(15)
    end
    
    properties (Dependent)
        Status
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Status'} % List of non-constant message properties
        ROSPropertyList = {'status'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = Wiper(msg)
            %Wiper Construct the message object Wiper
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
        
        function status = get.Status(obj)
            %get.Status Get the value for property Status
            status = typecast(int8(obj.JavaMessage.getStatus), 'uint8');
        end
        
        function set.Status(obj, status)
            %set.Status Set the value for property Status
            validateattributes(status, {'numeric'}, {'nonempty', 'scalar'}, 'Wiper', 'Status');
            
            obj.JavaMessage.setStatus(status);
        end
    end
    
    methods (Access = protected)
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Status = obj.Status;
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Status = strObj.Status;
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
            
            strObj.Status = obj.Status;
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.dbw_mkz_msgs.Wiper.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.dbw_mkz_msgs.Wiper;
            obj.reload(strObj);
        end
    end
end
