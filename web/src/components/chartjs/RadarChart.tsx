import { Radar } from 'react-chartjs-2';
import { Chart as ChartJS, RadialLinearScale, PointElement, LineElement, Title, Tooltip, Legend } from 'chart.js';

ChartJS.register(RadialLinearScale, PointElement, LineElement, Title, Tooltip, Legend);

export interface dataSet {
  label: string;
  data: number[];
  fill: boolean;
  backgroundColor: string;
  borderColor: string;
  pointBackgroundColor: string;
  pointBorderColor: string;
  pointHoverBackgroundColor: string;
  pointHoverBorderColor: string;
}

export interface radarData {
  labels: string[];
  datasets: dataSet[];
}


interface RadarAnimationOptions {
  duration: number;
}

interface radarOptions {
  animation?: RadarAnimationOptions;
}

interface RadarChartProps {
  data?: radarData;
  option?: radarOptions;
}

const radarData: radarData = {
    labels: [
        'Move up',
        'Move down',
        'Move left',
        'Move right',
      ],
      datasets: [{
        label: 'Player 1',
        data: [65, 59, 90, 81],
        fill: true,
        backgroundColor: 'rgba(255, 99, 132, 0.2)',
        borderColor: 'rgb(255, 99, 132)',
        pointBackgroundColor: 'rgb(255, 99, 132)',
        pointBorderColor: '#fff',
        pointHoverBackgroundColor: '#fff',
        pointHoverBorderColor: 'rgb(255, 99, 132)'
      }, {
        label: 'Player 2',
        data: [28, 48, 40, 19],
        fill: true,
        backgroundColor: 'rgba(54, 162, 235, 0.2)',
        borderColor: 'rgb(54, 162, 235)',
        pointBackgroundColor: 'rgb(54, 162, 235)',
        pointBorderColor: '#fff',
        pointHoverBackgroundColor: '#fff',
        pointHoverBorderColor: 'rgb(54, 162, 235)'
      }]
};

const radarOptions : radarOptions = {
  animation: {
    duration: 2000,
  },

};



const RadarChart: React.FC<RadarChartProps> = ({data, option}) => {

  const chartDat = data || radarData;
  const chartOpt = option || radarOptions 

  return (
    <Radar data={chartDat} options={chartOpt} />
  );
}

export default RadarChart;
