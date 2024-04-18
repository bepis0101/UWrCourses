import * as Tabs from '@radix-ui/react-tabs';
import LabelDemo from '../Label/Label';
import RadioGroupDemo from '../Radio/Radio';
import SelectDemo from '../Select/Select';
import './styles.css';
import SliderDemo from '../Slider/Slider';
import SwitchDemo from '../Switch/Switch';

const TabsDemo = () => (
  <Tabs.Root className="TabsRoot" defaultValue="tab1">
    <Tabs.List className="TabsList" aria-label="Manage your account">
      <Tabs.Trigger className="TabsTrigger" value="tab1">
        Account
      </Tabs.Trigger>
      <Tabs.Trigger className="TabsTrigger" value="tab2">
        Password
      </Tabs.Trigger>
      <Tabs.Trigger className="TabsTrigger" value="tab3">
        Preferences
      </Tabs.Trigger>
    </Tabs.List>
    <Tabs.Content className="TabsContent" value="tab1">
      <p className="Text">Make changes to your account here. Click save when you're done.</p>
      <LabelDemo label="Name" type="text"/>
      <LabelDemo label="Username" type="text" />
      <p>Gender:</p>
      <RadioGroupDemo labels={['male', 'female', 'other']} />
      <div style={{ display: 'flex', marginTop: 20, justifyContent: 'flex-end' }}>
        <button className="Button green">Save changes</button>
      </div>
    </Tabs.Content>
    <Tabs.Content className="TabsContent" value="tab2">
      <p className="Text">Change your password here. After saving, you'll be logged out.</p>
      <LabelDemo label="Current password" type="password" />
      <LabelDemo label="New password" type="password" />
      <LabelDemo label="Confirm password" type="password" />
      <div style={{ display: 'flex', marginTop: 20, justifyContent: 'flex-end' }}>
        <button className="Button green">Change password</button>
      </div>
    </Tabs.Content>
    <Tabs.Content className="TabsContent" value="tab3">
      <p className="Text">
        Change preferences here. Click save when you're done.
      </p>
      <form className="FormPref">
        <label htmlFor="select">
          Notification settings:
        </label>
        <SelectDemo />
        <label htmlFor="freq">
          Notfication frequency:
        </label>
        <SliderDemo />
        <SwitchDemo label="Additional data:" />
      </form>
    </Tabs.Content>
  </Tabs.Root>
);

export default TabsDemo;