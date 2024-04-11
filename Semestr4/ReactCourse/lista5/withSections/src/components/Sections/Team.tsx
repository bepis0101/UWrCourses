import Section from "../Sections";

interface TeamProps {
  id: number;
  name: string;
  position: string;
  image: string;
  bio: string;
}

export default function Team(team: TeamProps[]) {
  <Section id="team">
    <h2>Our Team</h2>
    <div className="team-members">
      {team.map((member) => (
        <div key={member.id} className="team-member">
          <img src={member.image} alt={member.name} />
          <div>
            <h3>{member.name}</h3>
            <p>{member.position}</p>
            <p>{member.bio}</p>
          </div>
        </div>
      ))}
    </div>
  </Section>
}