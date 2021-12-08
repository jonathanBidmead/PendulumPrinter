function sortedLine =  lineSort(testLines)

testLines = [nonzeros(testLines(:,1)) nonzeros(testLines(:,2))];

%find end position (either one)
count  = zeros(length(testLines),1);
for i = 1:length(testLines)
    px = testLines(i,:);
    for j = 1:length(testLines)
        testPx = testLines(j,:);
        if (abs(px(1) - testPx(1)) < 2 && abs(px(2) - testPx(2)) < 2)
           count(i) = count(i) + 1; 
        end
    end
end

mindices = find(count == min(count));%TODO: maybe change to some sort of localmin thing

%choose one of the mindices(somehow)
px = testLines(mindices(1),:);
% px = testLines(248,:);
sortedLine = px;
adj = [];
k = 1;
condition = 0;
badPixels = 0;

while (condition < length(testLines))
    k = 1;
    
    %debug
%     if condition == 204
%        a = 0; 
%     end
    
    for j = 1:length(testLines)%test to find all adjacent pixels
        testPx = testLines(j,:);
        if (abs(px(1) - testPx(1)) < 2 && abs(px(2) - testPx(2)) < 2)
            adj(k,:) = testPx;
            k = k+1;
        end
    end
    
    for i = 1:length(adj)%removing all elements already sorted
        if (ismember(adj(i,:),sortedLine,'rows'))
            adj(i,1) = 0;
            adj(i,2) = 0;
        end
    end
    
    nadj = [nonzeros(adj(:,1)) nonzeros(adj(:,2))];
    
    %if only one adjacent pixel
    if (size(nadj,1) == 1)
       px = nonzeros(adj);
       sortedLine(end+1,:) = px;
    
    %if two adjacent pixels
    elseif (size(nadj,1) == 2)
        for j = 1:length(nadj)
            
            if (sqrt((nadj(j,1) - px(1))^2 + (nadj(j,2) - px(2))^2) < 1.2)
                px = nadj(j,:);
                sortedLine(end+1,:) = px;
            end
        end
    
    else
        badPixels = condition;
    end
    
    condition = condition + 1;
end