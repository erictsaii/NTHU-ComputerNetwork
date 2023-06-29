load('network_A.mat')
%initialize
d=A;
for i=1:100
    for j=1:100
        if d(i,j)==0
            d(i,j)=99999;
        end
        if i==j
            d(i,j)=0;
        end
    end
end
%floyd warshall
for k=1:100
    for u=1:100
        for v=1:100
            if d(u,v)>d(u,k)+d(k,v)
                d(u,v)=d(u,k)+d(k,v);
            end
        end
    end
end
%save result
save('result.mat', 'd')


