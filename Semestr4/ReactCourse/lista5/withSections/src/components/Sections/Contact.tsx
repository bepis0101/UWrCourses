import React from "react";
import Section from "../Sections";

export default function Contact(handleSubmit: (event: React.FormEvent<HTMLFormElement>) => void) {
  return (
    <Section id="contact">
      <div className="section-content">
        <h2>Contact Us</h2>
        <form onSubmit={handleSubmit} className="contact-form">
          <div className="form-group">
            <input type="text" placeholder="Name" required />
          </div>
          <div className="form-group">
            <input type="email" placeholder="Email" required />
          </div>
          <div className="form-group">
            <textarea rows={5} placeholder="Message" required></textarea>
          </div>
          <button type="submit">Send Message</button>
        </form>
      </div>
    </Section>
  )
}