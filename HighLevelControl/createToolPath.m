%run interpretingImage from this script
interpretingImage;

%sort lines output from interpretingImage so that all adjacent pixels are
%next to each other
for i = 1:2:size(lines,2)
    sortedLine(1:size(nonzeros(lines(:,i)),1),i:i+1) = lineSort(lines(:,i:i+1));
end

%use lines output from interpretingImage as input to Kinematics to create a
%toolpath for the robot

%scale output of interpretingImage from pixels to mm
%conversion factor 2.93
lines_mm = sortedLine./2.93;

lineNum = 1;

refX = nonzeros(lines_mm(:,lineNum+1));
refY = nonzeros(lines_mm(:,lineNum));

%calculating offset relative to base location
baseX = 150;
baseY = 220;
% lines_mm(:,lineNum+1) = lines_mm(:,lineNum+1) - baseX;
% lines_mm(:,lineNum) = lines_mm(:,lineNum) - baseY;

refX = refX - baseX;
refY = refY - baseY;

% refPath = Kinematics([nonzeros(lines_mm(:,lineNum+1)+baseX)-baseX nonzeros(lines_mm(:,lineNum)+baseY)-baseY]);

refPath = Kinematics([refX refY]);

%converting back to cartesian to check accuracy
r1 = 160;
r2 = 180;

theta1 = refPath(:,1);
theta2 = refPath(:,2);
t = length(refPath);


p0 = [baseX.*ones(1,t); baseY.*ones(1,t)];
p1 = [p0(1,:) + r1.*cos(theta1)'; p0(2,:) + r1.*sin(theta1)'];
p2 = [p1(1,:) + r2.*cos(theta1 + theta2)'; p1(2,:) + r2.*sin(theta1 + theta2)'];


h = animatedline('MaximumNumPoints',3);

hold on
set(gca, 'YDir','reverse')
axis ([-20 520 -20 530])
plot(refX+baseX, refY+baseY,'.')
for i = 1:t
    x = [p0(1,i) p1(1,i) p2(1,i)];
    y = [p0(2,i) p1(2,i) p2(2,i)];
    
    addpoints(h,x,y);
    pause(0.01);
    drawnow
end