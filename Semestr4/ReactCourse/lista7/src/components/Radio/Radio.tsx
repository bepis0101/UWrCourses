import * as RadioGroup from '@radix-ui/react-radio-group';
import './styles.css';

interface RadioGroupDemoProps {
  labels: string[];  
}

const RadioGroupDemo = ({ labels } : RadioGroupDemoProps) => (
  <form>
    <RadioGroup.Root className="RadioGroupRoot" defaultValue="default" aria-label="View density">
      {labels.map((label: string, index: number) => (
        <div style={{ display: 'flex', alignItems: 'center' }}>
          <RadioGroup.Item className="RadioGroupItem" value={label} id={index.toString()}>
            <RadioGroup.Indicator className="RadioGroupIndicator" />
          </RadioGroup.Item>
          <label className="Label" htmlFor={index.toString()}>
            {label}
          </label>
        </div>
      ))}
    </RadioGroup.Root>
  </form>
);

export default RadioGroupDemo;