import { Line } from 'react-chartjs-2';
import { Chart as ChartJS, CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend } from 'chart.js';

ChartJS.register(CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend);

const areaData = {
  labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
  datasets: [
    {
      label: 'Expenses',
      data: [30, 20, 40, 60, 80, 100],
      fill: true,
      backgroundColor: 'rgba(75, 192, 192, 0.2)',
      borderColor: 'rgb(75, 192, 192)',
      borderWidth: 1,
      tension: 0.1,
    },
  ],
};

const areaOptions = {
  animation: {
    duration: 2000,
  },
};

const AreaChart = () => <Line data={areaData} options={areaOptions} />;

export default AreaChart;
