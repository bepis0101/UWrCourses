import Section from "../Sections";

interface ServiceProps {
  id: number;
  name: string;
  description: string;
}

export default function Services(services: ServiceProps[]) {
  return (
    <Section id="services">
      <h2>Our Services</h2>
      <ul>
        {services.map((service) => (
          <li key={service.id}>
            <h3>{service.name}</h3>
            <p>{service.description}</p>
          </li>
        ))}
      </ul>
    </Section>
  );
}