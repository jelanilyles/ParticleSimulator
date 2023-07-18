
x = 1:499;


plot(x,estdhimsd,'b')


title('Gaussian vs Exponential at Varying Noise')
xlabel('Timestep'), ylabel('Mean Squared Displacement')



hold on;

% plot(gstdhimsd,'g');
% plot(estdlomsd,'k');
% plot(gstdlomsd,'y');
% plot(estdmidmsd,'c');
% plot(gstdmidmsd,'r');

hold off;

% legend('Exp Hi Noise', 'Gaus Hi Noise', 'Exp Lo Noise', 'Gaus Lo Noise', 'Exp Mid Noise', 'Gaus Mid Noise');
