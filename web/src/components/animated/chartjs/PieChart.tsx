import { Pie } from 'react-chartjs-2';
import { Chart as ChartJS, ArcElement, Title, Tooltip, Legend } from 'chart.js';

ChartJS.register(ArcElement, Title, Tooltip, Legend);

const pieData = {
  labels: ['Red', 'Blue', 'Yellow'],
  datasets: [
    {
      label: 'Votes',
      data: [300, 50, 100],
      backgroundColor: ['red', 'blue', 'yellow'],
      borderColor: 'rgba(0, 0, 0, 0.1)',
      borderWidth: 1,
    },
  ],
};

const pieOptions = {
  animation: {
    duration: 2000,
  },
};

const PieChart = () => <Pie data={pieData} options={pieOptions} />;

export default PieChart;
