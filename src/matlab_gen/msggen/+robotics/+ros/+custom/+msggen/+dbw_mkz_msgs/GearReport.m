classdef GearReport < robotics.ros.Message
    %GearReport MATLAB implementation of dbw_mkz_msgs/GearReport
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'dbw_mkz_msgs/GearReport' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '785b94d5bfee677e7f0da982153f2711' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant, Access = protected)
        DbwMkzMsgsGearClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dbw_mkz_msgs/Gear') % Dispatch to MATLAB class for message type dbw_mkz_msgs/Gear
        DbwMkzMsgsGearRejectClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dbw_mkz_msgs/GearReject') % Dispatch to MATLAB class for message type dbw_mkz_msgs/GearReject
        StdMsgsHeaderClass = robotics.ros.msg.internal.MessageFactory.getClassForType('std_msgs/Header') % Dispatch to MATLAB class for message type std_msgs/Header
    end
    
    properties (Dependent)
        Header
        State
        Cmd
        Reject
        Override
        FaultBus
    end
    
    properties (Access = protected)
        Cache = struct('Header', [], 'State', [], 'Cmd', [], 'Reject', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Cmd', 'FaultBus', 'Header', 'Override', 'Reject', 'State'} % List of non-constant message properties
        ROSPropertyList = {'cmd', 'fault_bus', 'header', 'override', 'reject', 'state'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = GearReport(msg)
            %GearReport Construct the message object GearReport
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
            validateattributes(header, {obj.StdMsgsHeaderClass}, {'nonempty', 'scalar'}, 'GearReport', 'Header');
            
            obj.JavaMessage.setHeader(header.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Header)
                obj.Cache.Header.setJavaObject(header.getJavaObject);
            end
        end
        
        function state = get.State(obj)
            %get.State Get the value for property State
            if isempty(obj.Cache.State)
                obj.Cache.State = feval(obj.DbwMkzMsgsGearClass, obj.JavaMessage.getState);
            end
            state = obj.Cache.State;
        end
        
        function set.State(obj, state)
            %set.State Set the value for property State
            validateattributes(state, {obj.DbwMkzMsgsGearClass}, {'nonempty', 'scalar'}, 'GearReport', 'State');
            
            obj.JavaMessage.setState(state.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.State)
                obj.Cache.State.setJavaObject(state.getJavaObject);
            end
        end
        
        function cmd = get.Cmd(obj)
            %get.Cmd Get the value for property Cmd
            if isempty(obj.Cache.Cmd)
                obj.Cache.Cmd = feval(obj.DbwMkzMsgsGearClass, obj.JavaMessage.getCmd);
            end
            cmd = obj.Cache.Cmd;
        end
        
        function set.Cmd(obj, cmd)
            %set.Cmd Set the value for property Cmd
            validateattributes(cmd, {obj.DbwMkzMsgsGearClass}, {'nonempty', 'scalar'}, 'GearReport', 'Cmd');
            
            obj.JavaMessage.setCmd(cmd.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Cmd)
                obj.Cache.Cmd.setJavaObject(cmd.getJavaObject);
            end
        end
        
        function reject = get.Reject(obj)
            %get.Reject Get the value for property Reject
            if isempty(obj.Cache.Reject)
                obj.Cache.Reject = feval(obj.DbwMkzMsgsGearRejectClass, obj.JavaMessage.getReject);
            end
            reject = obj.Cache.Reject;
        end
        
        function set.Reject(obj, reject)
            %set.Reject Set the value for property Reject
            validateattributes(reject, {obj.DbwMkzMsgsGearRejectClass}, {'nonempty', 'scalar'}, 'GearReport', 'Reject');
            
            obj.JavaMessage.setReject(reject.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Reject)
                obj.Cache.Reject.setJavaObject(reject.getJavaObject);
            end
        end
        
        function override = get.Override(obj)
            %get.Override Get the value for property Override
            override = logical(obj.JavaMessage.getOverride);
        end
        
        function set.Override(obj, override)
            %set.Override Set the value for property Override
            validateattributes(override, {'logical', 'numeric'}, {'nonempty', 'scalar'}, 'GearReport', 'Override');
            
            obj.JavaMessage.setOverride(override);
        end
        
        function faultbus = get.FaultBus(obj)
            %get.FaultBus Get the value for property FaultBus
            faultbus = logical(obj.JavaMessage.getFaultBus);
        end
        
        function set.FaultBus(obj, faultbus)
            %set.FaultBus Set the value for property FaultBus
            validateattributes(faultbus, {'logical', 'numeric'}, {'nonempty', 'scalar'}, 'GearReport', 'FaultBus');
            
            obj.JavaMessage.setFaultBus(faultbus);
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.Header = [];
            obj.Cache.State = [];
            obj.Cache.Cmd = [];
            obj.Cache.Reject = [];
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
            cpObj.Override = obj.Override;
            cpObj.FaultBus = obj.FaultBus;
            
            % Recursively copy compound properties
            cpObj.Header = copy(obj.Header);
            cpObj.State = copy(obj.State);
            cpObj.Cmd = copy(obj.Cmd);
            cpObj.Reject = copy(obj.Reject);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Override = strObj.Override;
            obj.FaultBus = strObj.FaultBus;
            obj.Header = feval([obj.StdMsgsHeaderClass '.loadobj'], strObj.Header);
            obj.State = feval([obj.DbwMkzMsgsGearClass '.loadobj'], strObj.State);
            obj.Cmd = feval([obj.DbwMkzMsgsGearClass '.loadobj'], strObj.Cmd);
            obj.Reject = feval([obj.DbwMkzMsgsGearRejectClass '.loadobj'], strObj.Reject);
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
            
            strObj.Override = obj.Override;
            strObj.FaultBus = obj.FaultBus;
            strObj.Header = saveobj(obj.Header);
            strObj.State = saveobj(obj.State);
            strObj.Cmd = saveobj(obj.Cmd);
            strObj.Reject = saveobj(obj.Reject);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.dbw_mkz_msgs.GearReport.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.dbw_mkz_msgs.GearReport;
            obj.reload(strObj);
        end
    end
end
