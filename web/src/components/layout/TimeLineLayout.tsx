import { VerticalTimeline, VerticalTimelineElement } from "react-vertical-timeline-component";
import "./TimeLine.css"

interface Event {
  time: string;
  message: string;
}

interface Props {
  events: Event[];
}

export default function LiveEventTimeline({ events }: Props) {
  return (
    <div style={{ maxWidth: "80vh", margin: "0 auto", overflow: "visible"}}>
      <h2 style={{ textAlign: "center" }}>Timeline des Événements</h2>
      <VerticalTimeline>
        {events.map((event, index) => (
          <VerticalTimelineElement
            key={index}
            date={event.time}
            dateClassName="date"
            iconStyle={{ background: "#06D6A0", color: "#fff"}}
            contentStyle={{background: "#f9f9f9", color: "#f9f9f9", borderRadius: "8px", wordWrap: "break-word", overflowWrap: "break-word", whiteSpace: "normal"}}
            contentArrowStyle={{ borderRight: "7px solid #f9f9f9" }}
          >
            <h3 style={{color:"#333"}}>{event.message}</h3>
          </VerticalTimelineElement>
        ))}
      </VerticalTimeline>
    </div>
  );
}
