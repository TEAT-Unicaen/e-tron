import React, { useState } from "react";
import { Slider, Box, Typography } from "@mui/material";

interface RangeSelectorProps {
  min: number;
  max: number;
  onChange: (range: [number, number]) => void;
}

const RangeSelector: React.FC<RangeSelectorProps> = ({ min, max, onChange }) => {
  const [value, setValue] = useState<[number, number]>([min, max]);

  const handleChange = (_event: Event, newValue: number | number[]) => {
    if (Array.isArray(newValue)) {
      setValue(newValue as [number, number]);
      onChange(newValue as [number, number]);
    }
  };

  return (
    <Box width={300} p={2}>
      <Typography variant="h6">Plage sélectionnée: {value[0]} - {value[1]}</Typography>
      <Slider
        value={value}
        onChange={handleChange}
        valueLabelDisplay="auto"
        min={min}
        max={max}
      />
    </Box>
  );
};

export default RangeSelector;
