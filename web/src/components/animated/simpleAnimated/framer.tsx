import { motion } from "framer-motion";
import { useEffect, useState } from "react";

type AnimatedNumberProps = {
  value: number;
  max?: number;
};

const AnimatedNumber: React.FC<AnimatedNumberProps> = ({ value, max = 100 }) => {
  const [displayValue, setDisplayValue] = useState(0);

  useEffect(() => {
    let interval = setInterval(() => {
      setDisplayValue((prev) => {
        if (prev >= value) {
          clearInterval(interval);
          return value;
        }
        return prev + Math.ceil(value / 50);
      });
    }, 20);
    return () => clearInterval(interval);
  }, [value]);

  return (
    <div className="flex flex-col items-center w-full max-w-sm mx-auto">
      <motion.span
        className="text-4xl font-bold text-blue-500 mb-2"
        animate={{ opacity: [0, 1], scale: [0.8, 1] }}
        transition={{ duration: 0.5 }}
      >
        {displayValue}
      </motion.span>
      <div className="w-full bg-gray-300 rounded-full h-6 overflow-hidden">
        <motion.div
          className="bg-blue-500 h-6"
          initial={{ width: 0 }}
          animate={{ width: `${(value / max) * 100}%` }}
          transition={{ duration: 1 }}
        />
      </div>
    </div>
  );
};

export default AnimatedNumber;