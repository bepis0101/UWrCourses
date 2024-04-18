import * as Label from '@radix-ui/react-label';
import './styles.css';

interface LabelDemoProps {
  label: string;
  type: string;
}

const LabelDemo = ({ label, type }: LabelDemoProps) => (
  <div
    style={{ display: 'flex', padding: '0 20px', flexWrap: 'wrap', gap: 15, alignItems: 'center', width: '100%'}}
  >
    <fieldset className="Fieldset">
      <Label.Root className="LabelRoot" htmlFor={label}>
        {label}
      </Label.Root>
      <input className="Input" type={type} id={label} defaultValue="" />
    </fieldset>
  </div>
);

export default LabelDemo;