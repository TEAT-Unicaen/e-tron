import React, {useState, useEffect} from "react";
import styles from "./Glower.module.scss";

interface GlowerProps {
    width?: number;
    height?: number;
    color?: string;
    borderRadius?: number;
    opacity?: number;
    top?: number;
    left?: number;
    rotation?: number;
    blur?: number;
}

const Glower: React.FC<GlowerProps> = ({
    width = 30,
    height = 20,
    color = "#ffffff",
    borderRadius = 100,
    opacity = 0.05,
    top = 50,
    left = 100,
    rotation = 30,
    blur = 20,
}) => {

    const [animatedOpacity, setAnimatedOpacity] = useState(opacity);
    const [startTime, setStartTime] = useState<number | null>(null);

    useEffect(() => {
        const delay = Math.random() * 2000;
        
        const timeout = setTimeout(() => {
            setStartTime(performance.now()); 
        }, delay);

        return () => clearTimeout(timeout);
    }, []);

    useEffect(() => {
        if (startTime === null) return;
        const animate = (timestamp: number) => {
            const elapsed = timestamp - startTime;
            const oscillation = Math.sin(elapsed / 1000) * 0.1; 
            setAnimatedOpacity(opacity + opacity * oscillation);
            requestAnimationFrame(animate);
        };

        const animationFrame = requestAnimationFrame(animate);
        return () => cancelAnimationFrame(animationFrame);
    }, [startTime, opacity]);


    return (
        <div
            className={styles.glower}
            style={{
                width: `${width}vh`,
                height: `${height}vh`,
                backgroundColor: color,
                borderRadius: `${borderRadius}vh`,
                opacity: animatedOpacity,
                top : `${top}vh`,
                left : `${left}vh`,
                transform: `rotate(${rotation}deg)`,
                filter: `blur(${blur}px)`,
            }}
        />
    );
}

export default Glower;