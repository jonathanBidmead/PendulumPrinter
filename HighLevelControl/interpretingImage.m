clear
canvas = imread('workingCanvas.png');
count = 0;
k = 1;

for i = 1:size(canvas,1)%for each row
    for j = 1:size(canvas,2)%for each col
        if canvas(i,j,1) < 255%if pixel is black
            %find all black pixels
            blackPixels(k,1) = i;
            blackPixels(k,2) = j;
            k = k + 1;
        end
    end
end

%getting all lines in image
startRow = blackPixels(1,1);
startCol = blackPixels(1,2);
adj = [-1,-1];
newCondition = true;
m = 1;
% lines = zeros(length(blackPixels),100);
while(newCondition)

    blackPixels = setdiff(blackPixels,adj,'rows');
    
    if length(blackPixels) < 1
        break
    end
    
    %[single iteration] get a point in blackPixels and find everything adjacent
    %to it
    startRow = blackPixels(1,1);
    startCol = blackPixels(1,2);
    condition = true;
    j = 2;
    start = 2;
    adj = [startRow,startCol];
    count = 0;
    
    
    
    while(condition)
        for a = start-1:length(adj)
            start = length(adj)
            startRow = adj(a,1);
            startCol = adj(a,2);
            for i = 1:length(blackPixels)%gets pixels adjacent to startPx
                if (abs(startRow - blackPixels(i,1)) < 3) && (abs(startCol - blackPixels(i,2)) < 3)%if abs diff between given pixel and a black pixel is < 2, (i.e. they're adjacent

                    if ~ismember([blackPixels(i,1),blackPixels(i,2)],adj,'rows')%check whether the point is already in the adjacent list
                        adj(j,1) = blackPixels(i,1);
                        adj(j,2) = blackPixels(i,2);
                        j = j + 1;
                        count = 0;
                    end

                end
            end
        end
        count = count + 1;
        if (count > 3)
            condition = false;
        end
    end

    lines(1:length(adj),m:m+1) = adj;
    m = m + 2;
    
end




