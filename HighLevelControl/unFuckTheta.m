epsilon = 0.5;
theta1_new = zeros(length(theta1),1);

% for i = 2:length(theta1)-1
%     theta1_new(i) = theta1(i);
%     if (abs(theta1(i) - theta1(i-1)) > epsilon)
%         theta1_new(i:end) = theta1(i:end) + pi;
%         break
%     end
% end


for i = 1:length(theta1)
    if (theta1(i) > 0)
        theta1(i) = theta1(i) - pi;
    end
    
end

for i = 1:length(theta2)
    if (theta2(i) > 0)
        theta2(i) = theta2(i) - pi;
    end
    
end