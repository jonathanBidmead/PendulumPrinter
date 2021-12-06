r1 = 1;
r2 = 1;
t = 100;
refX = linspace(0.1,1,t);
refY = linspace(0.1,1,t);

refX = linspace(0,1.5,t);
refY = 1.*sin(2.*refX);

theta2 = acos((refX.^2 + refY.^2 - r1^2 - r2^2)/(2*r1*r2));
theta1 = atan(refY./refX) - atan((r2.*sin(theta2))./(r1+r2.*cos(theta2)));


p0 = [zeros(1,t); zeros(1,t)];
p1 = [r1.*cos(theta1); r1.*sin(theta1)];
p2 = [p1(1,:) + r2.*cos(theta1 + theta2); p1(2,:) + r2.*sin(theta1 + theta2)];

h = animatedline('MaximumNumPoints',3);

hold on
axis([-2 2 -2 2]);
plot(refX,refY)
for i = 1:t
    x = [p0(1,i) p1(1,i) p2(1,i)];
    y = [p0(2,i) p1(2,i) p2(2,i)];
    
    addpoints(h,x,y);
    pause(0.01);
    drawnow
end

