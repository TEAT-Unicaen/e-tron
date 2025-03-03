import { Doughnut } from 'react-chartjs-2';
import { Chart as ChartJS, ArcElement, Title, Tooltip, Legend } from 'chart.js';

ChartJS.register(ArcElement, Title, Tooltip, Legend);

const doughnutData = {
  labels: ['Red', 'Green', 'Blue'],
  datasets: [
    {
      data: [350, 200, 100],
      backgroundColor: ['red', 'green', 'blue'],
      borderColor: 'rgba(0, 0, 0, 0.1)',
      borderWidth: 1,
    },
  ],
};

const doughnutOptions = {
  animation: {
    duration: 2000,
  },
};

const DoughnutChart = () => <Doughnut data={doughnutData} options={doughnutOptions} />;

export default DoughnutChart;
