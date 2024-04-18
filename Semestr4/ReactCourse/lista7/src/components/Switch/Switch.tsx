import * as Switch from '@radix-ui/react-switch';
import './styles.css';

interface SwitchProps {
  label: string;
}

const SwitchDemo = ({ label }: SwitchProps) => (
  <form>
    <div style={{ display: 'flex', alignItems: 'center' }}>
      <label className="Label" htmlFor={label} style={{ paddingRight: 15 }}>
        {label}
      </label>
      <Switch.Root className="SwitchRoot" id={label}>
        <Switch.Thumb className="SwitchThumb" />
      </Switch.Root>
    </div>
  </form>
);

export default SwitchDemo;