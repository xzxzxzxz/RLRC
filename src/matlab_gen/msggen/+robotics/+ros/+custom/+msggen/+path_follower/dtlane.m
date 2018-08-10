classdef dtlane < robotics.ros.Message
    %dtlane MATLAB implementation of path_follower/dtlane
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'path_follower/dtlane' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '1e60021b42021278e47be71f881d31aa' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Dependent)
        Dist
        Dir
        Apara
        R
        Slope
        Cant
        Lw
        Rw
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Apara', 'Cant', 'Dir', 'Dist', 'Lw', 'R', 'Rw', 'Slope'} % List of non-constant message properties
        ROSPropertyList = {'apara', 'cant', 'dir', 'dist', 'lw', 'r', 'rw', 'slope'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = dtlane(msg)
            %dtlane Construct the message object dtlane
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
        
        function dist = get.Dist(obj)
            %get.Dist Get the value for property Dist
            dist = double(obj.JavaMessage.getDist);
        end
        
        function set.Dist(obj, dist)
            %set.Dist Set the value for property Dist
            validateattributes(dist, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Dist');
            
            obj.JavaMessage.setDist(dist);
        end
        
        function dir = get.Dir(obj)
            %get.Dir Get the value for property Dir
            dir = double(obj.JavaMessage.getDir);
        end
        
        function set.Dir(obj, dir)
            %set.Dir Set the value for property Dir
            validateattributes(dir, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Dir');
            
            obj.JavaMessage.setDir(dir);
        end
        
        function apara = get.Apara(obj)
            %get.Apara Get the value for property Apara
            apara = double(obj.JavaMessage.getApara);
        end
        
        function set.Apara(obj, apara)
            %set.Apara Set the value for property Apara
            validateattributes(apara, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Apara');
            
            obj.JavaMessage.setApara(apara);
        end
        
        function r = get.R(obj)
            %get.R Get the value for property R
            r = double(obj.JavaMessage.getR);
        end
        
        function set.R(obj, r)
            %set.R Set the value for property R
            validateattributes(r, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'R');
            
            obj.JavaMessage.setR(r);
        end
        
        function slope = get.Slope(obj)
            %get.Slope Get the value for property Slope
            slope = double(obj.JavaMessage.getSlope);
        end
        
        function set.Slope(obj, slope)
            %set.Slope Set the value for property Slope
            validateattributes(slope, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Slope');
            
            obj.JavaMessage.setSlope(slope);
        end
        
        function cant = get.Cant(obj)
            %get.Cant Get the value for property Cant
            cant = double(obj.JavaMessage.getCant);
        end
        
        function set.Cant(obj, cant)
            %set.Cant Set the value for property Cant
            validateattributes(cant, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Cant');
            
            obj.JavaMessage.setCant(cant);
        end
        
        function lw = get.Lw(obj)
            %get.Lw Get the value for property Lw
            lw = double(obj.JavaMessage.getLw);
        end
        
        function set.Lw(obj, lw)
            %set.Lw Set the value for property Lw
            validateattributes(lw, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Lw');
            
            obj.JavaMessage.setLw(lw);
        end
        
        function rw = get.Rw(obj)
            %get.Rw Get the value for property Rw
            rw = double(obj.JavaMessage.getRw);
        end
        
        function set.Rw(obj, rw)
            %set.Rw Set the value for property Rw
            validateattributes(rw, {'numeric'}, {'nonempty', 'scalar'}, 'dtlane', 'Rw');
            
            obj.JavaMessage.setRw(rw);
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
            cpObj.Dist = obj.Dist;
            cpObj.Dir = obj.Dir;
            cpObj.Apara = obj.Apara;
            cpObj.R = obj.R;
            cpObj.Slope = obj.Slope;
            cpObj.Cant = obj.Cant;
            cpObj.Lw = obj.Lw;
            cpObj.Rw = obj.Rw;
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Dist = strObj.Dist;
            obj.Dir = strObj.Dir;
            obj.Apara = strObj.Apara;
            obj.R = strObj.R;
            obj.Slope = strObj.Slope;
            obj.Cant = strObj.Cant;
            obj.Lw = strObj.Lw;
            obj.Rw = strObj.Rw;
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
            
            strObj.Dist = obj.Dist;
            strObj.Dir = obj.Dir;
            strObj.Apara = obj.Apara;
            strObj.R = obj.R;
            strObj.Slope = obj.Slope;
            strObj.Cant = obj.Cant;
            strObj.Lw = obj.Lw;
            strObj.Rw = obj.Rw;
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.path_follower.dtlane.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.path_follower.dtlane;
            obj.reload(strObj);
        end
    end
end