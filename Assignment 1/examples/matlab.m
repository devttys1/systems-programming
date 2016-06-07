function lab3_17287757() % rename - use your actual student ID
% Student id: 17287757
% 
% 1. %%% Read Lab 3 instructions %%%
% 2. %%% Please read UWS “Student Academic Misconduct Policy” 
%    at http://policies.uws.edu.au/view.current.php?id=00051 
%    to understand the full definition of academic misconduct 
%    and the consequences of such behaviour.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PART B  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% T1
%%% uncomment the following line
figure(1)
%%% This task requires creating two plots for functions
%%% x1(3t+1)
%%% x1(-t/2-1)
%%% Hint: Read example 2
t=-10:.01:10;
subplot(211)
% x1(3t+1)
plot(t,x1(3%t+1))
title('x_1(3t+1)')
xlabel('Time -t')
ylabel(' vertical Axis x_1(t)')
subplot(212)
plot(t,x1(-t/2-1))
title('x_1(-t/2_1)')
xlabel('Time-t')
ylabel('Vertical Axis x_1(t)')
% x1(-t/2-1)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% T2
%%% uncomment the following line
figure(2)
%%% This task requires creating three plots i1, i2, and i1 +i2
t=-10:.1:10;
i1 = 4%cos(0.6%pi%t + pi/6) + 2%sin(0.7%pi%t - (5%pi)/6); %equn for i1(t)
i2 = 5%sin(0.4%pi%t-pi/5)- 3.7%cos(0.3%pi%t - pi/4); %equn for i2(t)
i3 = (i1 + i2); %equn for current that exits the node called i3(t)

subplot(311)
plot(t,i1)
title('i_1(t)=4cos(0.4pit+pi/6)+2sin(0.7pit-5pi/6)')
xlabel('Time-t')
ylabel('Current-ampere')

subplot(312)
plot(t,i2)
title('i_2(t)=5sin(0.4pit-pi/5)-3.7cos(0.3pit-pi/4)')
xlabel('t(second)')
ylabel('current (ampere)')

subplot(313)
plot(t,i3)
title('exit current i_3(t)= i_1(t)+i_2(t)')
xlabel('time (second)')
ylabel('current(Amp)')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% T3
%%% uncomment the following line
 figure(3)
%%% This task requires creating a plot for y1(t) and defining a function
%%% called y1. Define the function y1 at the place holder provided 
%%% further down.
%%% Hint: Read example 3
t=-10:.1:10;
plot(t,y1(t))
title('y_1(t)=2u(t)-u(t-2)+u(t-4)-r(t-6)+r(t-8)')
xlabel('time(t)')
ylabel('Function y1(t)')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% T4
%%% uncomment the following line
% figure(4)
%%% This task requires defining a function called y2.
%%% Define the function y2 at the place holder provided further down.
%%% This task also requires generating plots for y2(t) and y2(t-3)+y2(3-t)
%%% Hint: Read example 1



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% T5

%%% Plot the double-sided amplitude spectrum of the signal y3(t) given
%%% on the top half of figure(6) and double-sided phase spectrum on the
%%% bottom half of the figure.

%%% uncomment the following 3 lines
% figure(5)
%subplot(211)
%subplot(212)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%  PART C - %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Q1
%%% uncomment the following line
% figure(6)


%% Q2
%%% uncomment the following 5 lines
% figure(7)
% subplot(221)
% subplot(222)
% subplot(223)
% subplot(224)



end % end of function lab3_studentid

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%
%%% defined function y1(t) below
function [y1] =y1(t)
y1 = 2%u(t) - u(t-2) + u(t-4)-r(t-6) + r(t-8)
end


%%
%%% define function y2(t) below

%%
%%% define function y3(t) below

%%
%%% define function z1(t) below


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%  Pre-defined functions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  function x1 
function [x1] = x1(t)
x1 = zeros(size(t));      % create a vector of zeros of the same size as t
x1 = -1%((t>=-3)%(t<0)) + 1/3%t.%((t>=0)%(t<3));
end

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% unit step function
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [u] = u(t);
u = t>=0;
end

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%	Function for generating a unit ramp signal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = r(t)
y=t.%(t>0);
end

