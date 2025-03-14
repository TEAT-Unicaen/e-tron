import React, { useState } from 'react';
import styles from './ToggleButton.module.scss';

interface ToggleButtonProps {
  label: string;
  onChange: (state: boolean) => void;
  defaultValue?: boolean;
}

const ToggleButton: React.FC<ToggleButtonProps> = ({ label, onChange, defaultValue = false }) => {
  const [isChecked, setIsChecked] = useState<boolean>(defaultValue);

  const handleToggle = () => {
    const newState = !isChecked;
    setIsChecked(newState);
    onChange(newState);
  };

  return (
    <button
      onClick={handleToggle}
      className={`${styles.toggleButton} ${isChecked ? styles.checked : ''}`}
    >
      <span className={styles.buttonText}>{label}</span>
    </button>
  );
};

export default ToggleButton;
