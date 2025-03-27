import { Line } from 'react-chartjs-2';
import { Chart as ChartJS, CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend } from 'chart.js';
import React from 'react';

ChartJS.register(CategoryScale, LinearScale, PointElement, LineElement, Title, Tooltip, Legend);

export type AreaData = {
  labels: string[];
  datasets: {
    label: string;
    data: number[];
    fill: boolean;
    backgroundColor: string;
    borderColor: string;
    borderWidth: number;
    tension: number;
  }[];
};

const areaOptions = {
  animation: {
    duration: 2000,
  },
};

const AreaChart: React.FC<{ data: AreaData }> = ({ data }) => {


  return <Line data={data} options={areaOptions} />;
}

export default AreaChart;
