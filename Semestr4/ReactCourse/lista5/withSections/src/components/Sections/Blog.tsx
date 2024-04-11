import Section from "../Sections";

interface BlogProps {
  id: number;
  title: string;
  date: string;
  content: string;
}


export default function Blog(blog: BlogProps[]) {
  return (
    <Section id="blog">
      <h2>Latest Blog Posts</h2>
      <div className="blog-posts">
        {blog.map((post) => (
          <div key={post.id} className="blog-post">
            <h3>{post.title}</h3>
            <p>{post.date}</p>
            <p>{post.content}</p>
            <button>Read More</button>
          </div>
        ))}
      </div>
    </Section>
  );
}