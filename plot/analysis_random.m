% load random=0.3
BLG(9,10,2)=0;
BLG(1,:,:)=load("../result/plot_BLG1_160_160.dat");
BLG(2,:,:)=load("../result/plot_BLG2_160_160.dat");
BLG(3,:,:)=load("../result/plot_BLG3_160_160.dat");
BLG(4,:,:)=load("../result/plot_BLG4_160_160.dat");
BLG(5,:,:)=load("../result/plot_BLG5_160_160.dat");
BLG(6,:,:)=load("../result/plot_BLG6_160_160.dat");
BLG(7,:,:)=load("../result/plot_BLG7_160_160.dat");
BLG(8,:,:)=load("../result/plot_BLG8_160_160.dat");
BLG(9,:,:)=load("../result/plot_BLG9_160_160.dat");

NG(9,10,2)=0;
NG(1,:,:)=load("../result/plot_NG1_160_160.dat");
NG(2,:,:)=load("../result/plot_NG2_160_160.dat");
NG(3,:,:)=load("../result/plot_NG3_160_160.dat");
NG(4,:,:)=load("../result/plot_NG4_160_160.dat");
NG(5,:,:)=load("../result/plot_NG5_160_160.dat");
NG(6,:,:)=load("../result/plot_NG6_160_160.dat");
NG(7,:,:)=load("../result/plot_NG7_160_160.dat");
NG(8,:,:)=load("../result/plot_NG8_160_160.dat");
NG(9,:,:)=load("../result/plot_NG9_160_160.dat");

LDG(9,10,2)=0;
LDG(1,:,:)=load("../result/plot_LDG1_160_160.dat");
LDG(2,:,:)=load("../result/plot_LDG2_160_160.dat");
LDG(3,:,:)=load("../result/plot_LDG3_160_160.dat");
LDG(4,:,:)=load("../result/plot_LDG4_160_160.dat");
LDG(5,:,:)=load("../result/plot_LDG5_160_160.dat");
LDG(6,:,:)=load("../result/plot_LDG6_160_160.dat");
LDG(7,:,:)=load("../result/plot_LDG7_160_160.dat");
LDG(8,:,:)=load("../result/plot_LDG8_160_160.dat");
LDG(9,:,:)=load("../result/plot_LDG9_160_160.dat");

blg(9,2)=0;
ng(9,2)=0;
ldg(9,2)=0;

for i = 1 : 9
    blg(i,:)= mean(BLG(i,:,:),2);
    ng(i,:)= mean(NG(i,:,:),2);
    ldg(i,:)= mean(LDG(i,:,:),2);
end
% % plot weight
% x=[0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9];
% hold on;
% plot(x,blg(:,1),'-r',"LineWidth",2);
% plot(x,ng(:,1),'-g',"LineWidth",2);
% plot(x,ldg(:,1),'-b',"LineWidth",2);
% legend("Baseline Greedy(BLG)", "Naive Greedy(NG)", "Linear Deterministic Greedy(LDG)");
% xlabel("Random Rate");
% ylabel("Weights ERROR");
% ylim([0 0.1]);

% plot edge
x=[0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9];
hold on;
plot(x,blg(:,2),'-r',"LineWidth",2);
plot(x,ng(:,2),'-g',"LineWidth",2);
plot(x,ldg(:,2),'-b',"LineWidth",2);
legend("Baseline Greedy(BLG)", "Naive Greedy(NG)", "Linear Deterministic Greedy(LDG)");
xlabel("Random Rate");
ylabel("Edges ERROR");

