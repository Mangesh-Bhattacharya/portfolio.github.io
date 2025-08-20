import React, { useEffect, useMemo, useState } from "react";
import { motion } from "framer-motion";
import { Github, Mail, Phone, MapPin, ExternalLink, Star, GitFork, Award, Shield, Terminal, MessageCircle, X, Linkedin } from "lucide-react";

/**
 * Futuristic/Realistic Cybersecurity Portfolio + Efficient On‑page Chatbot
 * - Dark neon aesthetic, glassmorphism cards, animated accents
 * - Live GitHub repo grid with filters
 * - Résumé, Education, TryHackMe-derived hackathon ideas, Certifications
 * - Floating chatbot (client‑side) that answers questions about: bio, LinkedIn, projects (with evidence links), education, certs, TryHackMe, and contact.
 * - Optional TTS voice for replies (Web Speech API)
 */

const RESUME = {
  name: "Mangesh Bhattacharya",
  title: "Cybersecurity Engineer",
  location: "Toronto, ON, Canada",
  phone: "+1 (416) 670-1418",
  email: "mangeshb20@gmail.com",
  github: "https://github.com/Mangesh-Bhattacharya",
  tryhackme: "https://tryhackme.com/p/TheOrbiter",
  linkedin: "https://www.linkedin.com/in/mangesh-bhattacharya/",
  summary:
    "Aspiring cybersecurity professional specializing in AI-driven threat detection, real-time monitoring, and automated security frameworks. Passionate about proactive threat intelligence and innovative solutions.",
  skills: {
    Programming: ["Python", "Java", "Bash", "PowerShell"],
    "Cybersecurity & Networking": ["Network Security", "IDS/IPS", "TCP/IP", "VPN", "Wireshark"],
    "Cloud & DevOps": ["AWS", "Azure", "GCP", "Docker", "Kubernetes", "CI/CD"],
    "Data & Viz": ["SQL", "Power BI", "Tableau", "OpenSearch"],
    "SecOps & Automation": ["SIEM", "Splunk", "ELK", "Threat Detection"],
    Collaboration: ["Git", "GitHub", "Jira", "Confluence"],
  },
  experience: [
    {
      role: "Cybersecurity Observability & Artificial Intelligence Engineer",
      company: "Ameya Cloud Solutions Inc.",
      location: "Mississauga, ON",
      dates: "Jan 2025 – May 2025",
      bullets: [
        "Designed and implemented real-time monitoring solutions for proactive threat detection.",
        "Developed ML-driven detection systems in Python; integrated OpenSearch for advanced log analysis.",
        "Automated incident response with AI-assisted playbooks; integrated SIEM/IDS/IPS telemetry.",
      ],
    },
    {
      role: "Cybersecurity Observability Engineer (Coop)",
      company: "Ameya Cloud Solutions Inc.",
      location: "Mississauga, ON",
      dates: "May 2024 – Nov 2024",
      bullets: [
        "Engineered safeguards with Snyk and Trivy to mitigate supply-chain vulnerabilities.",
        "Built detection tooling for proactive threat intel and designed automation frameworks.",
        "Created custom dashboards for monitoring and visualization across hybrid estates.",
      ],
    },
    {
      role: "Data Analyst (Intern)",
      company: "Ameya Cloud Solutions Inc.",
      location: "Mississauga, ON",
      dates: "Aug 2023 – Jan 2024",
      bullets: [
        "Implemented AWS security groups and automated dashboards to surface vulnerabilities.",
        "Conducted cloud security assessments and vulnerability analysis at scale.",
      ],
    },
  ],
  education: [
    {
      school: "Seneca College",
      program: "Bachelor of Information Technology — Cybersecurity",
      bullets: [
        "Focused on network security, incident response, and offensive security foundations.",
      ],
    },
    {
      school: "Humber College",
      program: "Network Engineering Diploma",
      bullets: [
        "Networking fundamentals, routing & switching, and hands-on lab work.",
      ],
    },
  ],
};

const CERTIFICATIONS = [
  { name: "Certificate of Cloud Security Knowledge (CCSK) V4", issuer: "Cloud Security Alliance", date: "Jun 8, 2023", link: "https://www.credly.com/badges/208450c6-b65a-4980-a1eb-ad3ac0113086/public_url" },
  { name: "Ethical Hacker — Course Completion", issuer: "Cisco Networking Academy", date: "Feb 26, 2025", link: "https://www.credly.com/badges/02e6a7b4-94fb-42a6-9f43-b645f84dac93/public_url" },
  { name: "Cisco Certified Network Associate (CCNA) — 200-301", issuer: "Cisco", date: "Jul 15, 2020", link: "https://www.credly.com/badges/65384268-681e-43ba-96d1-11b4b5b6ba0e/public_url" },
  { name: "Google IT Automation with Python — Professional Certificate", issuer: "Google/Coursera", date: "Jul 25, 2020", link: "" },
  { name: "Linear Algebra for Machine Learning and Data Science", issuer: "DeepLearning.AI / Coursera", date: "Feb 18, 2025", link: "" },
  { name: "PCEP — Certified Entry-Level Python Programmer", issuer: "Python Institute", date: "Jul 15, 2021", verify: "Code: XCHW.KC4j.AaEE" },
  { name: "Microsoft Certified: Azure Fundamentals (AZ-900)", issuer: "Microsoft", date: "Jan 17, 2021" },
  { name: "TryHackMe — Pre Security (Learning Path)", issuer: "TryHackMe", date: "Jan 19, 2025" },
  { name: "TryHackMe — Red Teaming (Learning Path)", issuer: "TryHackMe", date: "Jul 31, 2024" },
];

const HACKATHON_CHALLENGES = [
  { id: "rt-emulation", title: "Adversary Emulation: Initial Access → C2 → Lateral Movement", basedOn: ["THM: Red Teaming Path"], difficulty: "Advanced", description: "Build and demonstrate a full red-team chain in a lab: phishing or initial foothold, establish C2, enumerate, and laterally move to a high-value target. Provide a written OPORD and an after-action report.", deliverables: ["Attack plan (OPORD)", "Evidence & IOCs", "AAR write‑up"] },
  { id: "soc-detection", title: "SOC Detection & Response Dashboards", basedOn: ["SIEM", "OpenSearch", "ELK"], difficulty: "Intermediate", description: "Instrument a Windows/Linux lab, ship logs, and build detections for privilege escalation and lateral movement. Showcase dashboards and an automated enrichment pipeline.", deliverables: ["Detection rules", "Dashboards", "Runbook"] },
  { id: "presec-foundations", title: "Pre‑Security Foundations Capture-the-Flag", basedOn: ["THM: Pre Security Path"], difficulty: "Beginner", description: "Curate a CTF track with recon, web basics, and simple crypto/stego tasks. Newcomers complete tasks and submit flags along with short write-ups.", deliverables: ["Flags", "Write‑ups"] },
  { id: "cloud-hardening", title: "Cloud Hardening Sprint (Azure/AWS)", basedOn: ["AZ‑900", "CCSK"], difficulty: "Intermediate", description: "Secure a small multi-cloud footprint: identity, network segmentation, storage, and monitoring. Include a threat model and score improvements before/after.", deliverables: ["Threat model", "IaC policy", "Before/After metrics"] },
];

function Section({ id, title, children }) {
  return (
    <section id={id} className="py-16 scroll-mt-24">
      <div className="max-w-6xl mx-auto px-6">
        <h2 className="text-3xl font-bold tracking-tight mb-6 text-cyan-200 drop-shadow-[0_0_10px_rgba(34,211,238,0.35)]">{title}</h2>
        {children}
      </div>
    </section>
  );
}

function Pill({ children }) {
  return (
    <span className="inline-flex items-center rounded-full border border-white/10 bg-white/5 backdrop-blur px-3 py-1 text-sm mr-2 mb-2">{children}</span>
  );
}

function Chatbot({ repos }) {
  const [open, setOpen] = useState(false);
  const [input, setInput] = useState("");
  const [messages, setMessages] = useState([
    { role: "bot", html: "Hi! I’m <b>Orbiter</b>. Ask me about projects, certifications, education (Seneca, Humber), TryHackMe, LinkedIn, or how to contact Mangesh." },
  ]);
  const [tts, setTts] = useState(false);

  function speak(text) {
    try {
      if (!tts || typeof window === 'undefined' || !('speechSynthesis' in window)) return;
      const u = new SpeechSynthesisUtterance(text);
      u.rate = 1.03; u.pitch = 1; u.lang = 'en-US';
      window.speechSynthesis.cancel();
      window.speechSynthesis.speak(u);
    } catch {}
  }

  function stripTags(s) { return s.replace(/<[^>]*>/g, ''); }

  function evidenceRow(r) {
    const links = [
      `<a class='underline' href='${r.html_url}' target='_blank' rel='noreferrer'>repo</a>`,
      `<a class='underline' href='${r.html_url}/#readme' target='_blank' rel='noreferrer'>readme</a>`,
      `<a class='underline' href='${r.html_url}/commits' target='_blank' rel='noreferrer'>commits</a>`,
      r.homepage ? `<a class='underline' href='${r.homepage}' target='_blank' rel='noreferrer'>demo</a>` : null,
    ].filter(Boolean).join(" · ");
    return `<b>${r.name}</b>${r.language ? ` (${r.language})` : ''}${r.description ? ` — ${r.description}` : ''}. Evidence: ${links}. Updated ${new Date(r.updated_at).toLocaleDateString()}.`;
  }

  function answer(q) {
    const text = q.toLowerCase();

    // Intent routing
    const intents = {
      hello: /(hello|hi|hey|help|question|about you|who (are|is) (you|mangesh)|bio)/,
      contact: /(contact|email|reach|phone|call)/,
      linkedin: /(linkedin|profile|connect)/,
      projects: /(projects?|repos?|code|github|portfolio|accomplish|accomplished|evidence|details?)/,
      certs: /(cert|certificate|ccna|ccsk|azure|pcep|google|coursera)/,
      experience: /(experience|work|role|jobs?)/,
      education: /(seneca|humber|degree|diploma|education|college|university)/,
      tryhackme: /(tryhackme|red team|pre[- ]?security|ctf|hackathon)/,
    };

    let html = "I didn't catch that. Try asking about projects with evidence, LinkedIn, education (Seneca/Humber), certifications, TryHackMe, experience, or contact.";

    if (intents.hello.test(text)) {
      html = `<b>${RESUME.name}</b> is a cybersecurity engineer in ${RESUME.location}. Focus areas: AI‑assisted detection, threat intel, and automation. Current/previous roles at ${RESUME.experience[0].company}. Ask me for projects with evidence, LinkedIn, education, or certifications.`;
    }

    if (intents.linkedin.test(text)) {
      html = `LinkedIn: <a class='underline' href='${RESUME.linkedin}' target='_blank' rel='noreferrer'>${RESUME.linkedin}</a>.`;
    }

    if (intents.contact.test(text)) {
      html = `Contact: <a class='underline' href='mailto:${RESUME.email}'>${RESUME.email}</a> · ${RESUME.phone}`;
    }

    if (intents.projects.test(text)) {
      const top = repos.slice(0, 7).map(evidenceRow).join("<br/>");
      html = top || "I'm still loading repositories. Please try again in a moment.";
    }

    if (intents.certs.test(text)) {
      html = `Certifications:<br/>• ${CERTIFICATIONS.map(c=>`${c.name} — ${c.issuer} (${c.date})`).join('<br/>• ')}`;
    }

    if (intents.experience.test(text)) {
      html = RESUME.experience.map(e=>`<b>${e.role}</b> — ${e.company} (${e.dates})`).join('<br/>');
    }

    if (intents.education.test(text)) {
      html = RESUME.education.map(ed=>`<b>${ed.school}</b> — ${ed.program}${ed.bullets?.length?`: ${ed.bullets.join('; ')}`:''}`).join('<br/>');
    }

    if (intents.tryhackme.test(text)) {
      html = `TryHackMe: <a class='underline' href='${RESUME.tryhackme}' target='_blank' rel='noreferrer'>${RESUME.tryhackme}</a><br/>Highlighted challenges: ${HACKATHON_CHALLENGES.map(h=>h.title).slice(0,3).join('; ')}`;
    }

    const clean = stripTags(html);
    setMessages(prev => [...prev, { role: "user", html: q }, { role: "bot", html }]);
    speak(clean);
  }

  const quick = [
    { label: "About Mangesh", q: "Tell me about Mangesh" },
    { label: "Projects + Evidence", q: "Show projects accomplished with evidence" },
    { label: "Education (Seneca/Humber)", q: "What did you study at Seneca and Humber?" },
    { label: "LinkedIn", q: "Share your LinkedIn" },
    { label: "TryHackMe", q: "Show TryHackMe achievements" },
  ];

  return (
    <>
      <button onClick={()=>setOpen(true)} className="fixed bottom-6 right-6 z-50 inline-flex items-center gap-2 rounded-2xl border border-cyan-400/30 bg-cyan-400/10 text-cyan-200 px-4 py-2 backdrop-blur hover:bg-cyan-400/20">
        <MessageCircle className="w-4 h-4"/> Ask Orbiter
      </button>
      {open && (
        <div className="fixed inset-0 z-50 flex items-end sm:items-center justify-center bg-black/60">
          <div className="w-full sm:w-[38rem] max-h-[86vh] rounded-2xl border border-white/10 bg-slate-900/70 backdrop-blur p-4 shadow-2xl">
            <div className="flex items-center justify-between pb-2 border-b border-white/10">
              <div className="text-cyan-200 font-semibold">Orbiter — Portfolio Assistant</div>
              <div className="flex items-center gap-3">
                <label className="flex items-center gap-2 text-xs text-slate-300"><input type="checkbox" checked={tts} onChange={(e)=>setTts(e.target.checked)} /> Speak replies</label>
                <button onClick={()=>setOpen(false)} className="rounded-xl border border-white/10 p-1 hover:bg-white/5"><X className="w-4 h-4"/></button>
              </div>
            </div>
            <div className="mt-3 space-y-2 overflow-y-auto max-h-[56vh] pr-1">
              {messages.map((m,i)=> (
                <div key={i} className={m.role === 'bot' ? 'text-cyan-100' : 'text-slate-200'}>
                  <span className="text-xs uppercase tracking-wide mr-2 opacity-60">{m.role === 'bot' ? 'Orbiter' : 'You'}:</span>
                  {m.html ? <span dangerouslySetInnerHTML={{__html:m.html}}/> : m.text}
                </div>
              ))}
            </div>
            <div className="mt-3 flex flex-wrap gap-2 mb-2">
              {quick.map((qk)=> (
                <button key={qk.label} onClick={()=>answer(qk.q)} className="text-xs rounded-full border border-white/10 bg-white/5 px-2 py-1 hover:bg-white/10">{qk.label}</button>
              ))}
            </div>
            <div className="flex gap-2">
              <input value={input} onChange={(e)=>setInput(e.target.value)} onKeyDown={(e)=>{if(e.key==='Enter' && input.trim()){answer(input.trim()); setInput('')}}} placeholder="Ask a question…" className="flex-1 rounded-xl border border-white/10 bg-white/5 px-3 py-2 text-slate-100 placeholder:text-slate-400"/>
              <button onClick={()=>{if(input.trim()){answer(input.trim()); setInput('')}}} className="rounded-xl border border-cyan-400/30 bg-cyan-400/10 text-cyan-200 px-4 py-2">Send</button>
            </div>
          </div>
        </div>
      )}
    </>
  );
}

export default function Portfolio() {
  const [repos, setRepos] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState("");
  const [q, setQ] = useState("");
  const [lang, setLang] = useState("All");

  useEffect(() => {
    async function fetchRepos() {
      try {
        setLoading(true);
        const res = await fetch("https://api.github.com/users/Mangesh-Bhattacharya/repos?per_page=100&sort=updated", { headers: { Accept: "application/vnd.github+json", "X-GitHub-Api-Version": "2022-11-28" } });
        if (!res.ok) throw new Error(`GitHub API error ${res.status}`);
        const data = await res.json();
        const clean = data.filter(r=>!r.fork).map(r=>({ id:r.id, name:r.name, description:r.description, html_url:r.html_url, language:r.language||"", stars:r.stargazers_count, forks:r.forks_count, updated_at:r.updated_at, homepage:r.homepage })).sort((a,b)=> b.stars - a.stars);
        setRepos(clean);
      } catch (e) { setError(e.message); } finally { setLoading(false); }
    }
    fetchRepos();
  }, []);

  const languages = useMemo(() => { const set = new Set(["All"]); repos.forEach(r=> r.language && set.add(r.language)); return Array.from(set); }, [repos]);

  const filtered = useMemo(() => repos.filter(r=> { const matchQ = q ? (r.name + " " + (r.description || "")).toLowerCase().includes(q.toLowerCase()) : true; const matchLang = lang === "All" ? true : r.language === lang; return matchQ && matchLang; }), [q, lang, repos]);

  return (
    <div className="relative min-h-screen bg-gradient-to-b from-slate-950 via-slate-900 to-black text-slate-100">
      {/* Futuristic background grid */}
      <div className="pointer-events-none absolute inset-0 -z-10" aria-hidden>
        <div className="absolute inset-0 bg-[radial-gradient(ellipse_at_top,rgba(34,211,238,0.15),transparent_60%)]" />
        <div className="absolute inset-0 opacity-20" style={{backgroundImage:"linear-gradient(rgba(255,255,255,0.06) 1px, transparent 1px), linear-gradient(90deg, rgba(255,255,255,0.06) 1px, transparent 1px)", backgroundSize:"40px 40px"}} />
      </div>

      {/* Header */}
      <header className="sticky top-0 z-40 backdrop-blur bg-black/40 border-b border-white/10">
        <div className="max-w-6xl mx-auto px-6 py-4 flex items-center justify-between">
          <div className="font-semibold text-cyan-200 drop-shadow-[0_0_8px_rgba(34,211,238,0.5)]">{RESUME.name.split(" ")[0]}<span className="text-slate-500">.</span></div>
          <nav className="hidden sm:flex gap-6 text-sm">
            {[ ["about","About"],["experience","Experience"],["projects","Projects"],["education","Education"],["tryhackme","Hackathons"],["certs","Certifications"],["contact","Contact"]].map(([href,label])=> (
              <a key={href} href={`#${href}`} className="hover:text-cyan-200 transition">{label}</a>
            ))}
          </nav>
        </div>
      </header>

      {/* Hero */}
      <section className="py-16">
        <div className="max-w-6xl mx-auto px-6 grid md:grid-cols-3 gap-6 items-center">
          <div className="md:col-span-2">
            <h1 className="text-4xl md:text-5xl font-extrabold tracking-tight text-cyan-100 drop-shadow-[0_0_12px_rgba(34,211,238,0.35)]">{RESUME.name}</h1>
            <p className="mt-3 text-xl text-slate-300">{RESUME.title}</p>
            <p className="mt-4 max-w-2xl text-slate-300/90">{RESUME.summary}</p>
            <div className="mt-6 flex flex-wrap items-center gap-3">
              <a href={RESUME.github} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2 backdrop-blur hover:bg-white/10">
                <Github className="w-4 h-4"/> GitHub
              </a>
              <a href={RESUME.linkedin} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2 backdrop-blur hover:bg-white/10">
                <Linkedin className="w-4 h-4"/> LinkedIn
              </a>
              <a href={RESUME.tryhackme} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-cyan-400/30 bg-cyan-400/10 text-cyan-200 px-4 py-2 backdrop-blur hover:bg-cyan-400/20">
                <Shield className="w-4 h-4"/> TryHackMe
              </a>
            </div>
          </div>
          <div className="space-y-3 text-sm">
            <div className="flex items-center gap-2 opacity-90"><MapPin className="w-4 h-4"/> {RESUME.location}</div>
            <div className="flex items-center gap-2 opacity-90"><Phone className="w-4 h-4"/> {RESUME.phone}</div>
            <div className="flex items-center gap-2 opacity-90"><Mail className="w-4 h-4"/> <a href={`mailto:${RESUME.email}`} className="underline">{RESUME.email}</a></div>
          </div>
        </div>
      </section>

      {/* About / Skills */}
      <Section id="about" title="Skills">
        <div className="grid md:grid-cols-2 gap-6">
          {Object.entries(RESUME.skills).map(([group, items]) => (
            <div key={group} className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-5">
              <h3 className="font-semibold mb-3 text-slate-200">{group}</h3>
              <div>{items.map((s) => (<Pill key={s}>{s}</Pill>))}</div>
            </div>
          ))}
        </div>
      </Section>

      {/* Experience */}
      <Section id="experience" title="Experience">
        <div className="grid gap-6">
          {RESUME.experience.map((job) => (
            <motion.div key={job.role} initial={{ opacity: 0, y: 8 }} whileInView={{ opacity: 1, y: 0 }} viewport={{ once: true }} transition={{ duration: 0.4 }} className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-6">
              <div className="flex flex-wrap items-baseline justify-between gap-2">
                <h3 className="text-lg font-semibold text-slate-100">{job.role}</h3>
                <span className="text-sm text-slate-400">{job.dates}</span>
              </div>
              <div className="text-sm text-slate-300 mt-1">{job.company} — {job.location}</div>
              <ul className="mt-3 space-y-2 text-slate-200/90 list-disc pl-5">{job.bullets.map((b, i) => (<li key={i}>{b}</li>))}</ul>
            </motion.div>
          ))}
        </div>
      </Section>

      {/* Projects (GitHub) */}
      <Section id="projects" title="Projects (from GitHub)">
        <div className="mb-4 flex flex-wrap items-center gap-3">
          <input value={q} onChange={(e) => setQ(e.target.value)} placeholder="Search by name or description…" className="w-full md:w-80 rounded-xl border border-white/10 bg-white/5 px-3 py-2 placeholder:text-slate-500" />
          <select value={lang} onChange={(e) => setLang(e.target.value)} className="rounded-xl border border-white/10 bg-white/5 px-3 py-2">
            {languages.map((l) => (<option key={l} value={l}>{l}</option>))}
          </select>
        </div>
        {loading && <div className="text-slate-400">Loading repositories…</div>}
        {error && <div className="text-red-400">{error}</div>}
        {!loading && !error && (
          <div className="grid sm:grid-cols-2 lg:grid-cols-3 gap-5">
            {filtered.slice(0, 18).map((r) => (
              <a key={r.id} href={r.html_url} target="_blank" rel="noreferrer" className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-5 hover:shadow-[0_0_30px_rgba(34,211,238,0.15)] transition group">
                <div className="flex items-center justify-between">
                  <h3 className="font-semibold group-hover:text-cyan-200">{r.name}</h3>
                  <ExternalLink className="w-4 h-4 text-slate-400" />
                </div>
                {r.description && <p className="mt-1 text-sm text-slate-300">{r.description}</p>}
                <div className="mt-3 flex items-center gap-3 text-sm text-slate-400">
                  {r.language && <span>{r.language}</span>}
                  <span className="inline-flex items-center gap-1"><Star className="w-4 h-4"/> {r.stars}</span>
                  <span className="inline-flex items-center gap-1"><GitFork className="w-4 h-4"/> {r.forks}</span>
                </div>
                <div className="mt-2 text-xs text-slate-500">Updated {new Date(r.updated_at).toLocaleDateString()}</div>
              </a>
            ))}
          </div>
        )}
      </Section>

      {/* Education */}
      <Section id="education" title="Education">
        <div className="grid md:grid-cols-2 gap-6">
          {RESUME.education.map((ed)=> (
            <div key={ed.school} className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-6">
              <h3 className="text-lg font-semibold text-slate-100">{ed.school}</h3>
              <div className="text-sm text-slate-300">{ed.program}</div>
              {ed.bullets?.length ? (
                <ul className="mt-3 list-disc pl-5 text-slate-200/90">{ed.bullets.map((b,i)=>(<li key={i}>{b}</li>))}</ul>
              ) : null}
            </div>
          ))}
        </div>
      </Section>

      {/* TryHackMe / Hackathons */}
      <Section id="tryhackme" title="Hackathon Challenges (grounded in your learning paths)">
        <div className="mb-4 text-slate-300">Source profile: <a className="underline" href={RESUME.tryhackme} target="_blank" rel="noreferrer">{RESUME.tryhackme}</a></div>
        <div className="grid md:grid-cols-2 gap-5">
          {HACKATHON_CHALLENGES.map((c) => (
            <div key={c.id} className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-5">
              <div className="flex items-center justify-between">
                <h3 className="font-semibold text-slate-100">{c.title}</h3>
                <Terminal className="w-4 h-4 text-slate-400"/>
              </div>
              <div className="mt-1 text-xs text-slate-400">Based on: {c.basedOn.join(", ")}</div>
              <div className="mt-2 text-sm text-slate-300">{c.description}</div>
              <div className="mt-3 flex flex-wrap gap-2">
                <span className="text-xs rounded-full bg-white/5 border border-white/10 px-2 py-1">{c.difficulty}</span>
                {c.deliverables.map((d) => (<span key={d} className="text-xs rounded-full bg-white/5 border border-white/10 px-2 py-1">{d}</span>))}
              </div>
            </div>
          ))}
        </div>
      </Section>

      {/* Certifications */}
      <Section id="certs" title="Certifications & Learning Paths">
        <div className="grid sm:grid-cols-2 lg:grid-cols-3 gap-5">
          {CERTIFICATIONS.map((c, i) => (
            <div key={i} className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-5">
              <div className="flex items-center gap-2">
                <Award className="w-5 h-5 text-cyan-200"/>
                <h3 className="font-semibold text-slate-100">{c.name}</h3>
              </div>
              <div className="mt-1 text-sm text-slate-300">{c.issuer}</div>
              <div className="text-xs text-slate-400">{c.date}</div>
              {c.verify && <div className="mt-2 text-xs text-slate-400">{c.verify}</div>}
              {c.link && (
                <a href={c.link} target="_blank" rel="noreferrer" className="mt-3 inline-flex items-center gap-1 text-sm underline text-cyan-200">
                  Verify <ExternalLink className="w-4 h-4"/>
                </a>
              )}
            </div>
          ))}
        </div>
      </Section>

      {/* Contact */}
      <Section id="contact" title="Contact">
        <div className="rounded-2xl border border-white/10 bg-white/5 backdrop-blur p-6">
          <p className="text-slate-300">Open to roles in detection engineering, security automation, and red teaming. For collaborations, mentoring, or CTFs, reach out below.</p>
          <div className="mt-4 flex flex-wrap items-center gap-3 text-sm">
            <a href={`mailto:${RESUME.email}`} className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2"><Mail className="w-4 h-4"/> {RESUME.email}</a>
            <a href={RESUME.github} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2"><Github className="w-4 h-4"/> GitHub</a>
            <a href={RESUME.linkedin} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2"><Linkedin className="w-4 h-4"/> LinkedIn</a>
            <a href={RESUME.tryhackme} target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 rounded-2xl border border-white/10 bg-white/5 px-4 py-2"><Shield className="w-4 h-4"/> TryHackMe</a>
          </div>
        </div>
      </Section>

      <footer className="py-12 text-center text-xs text-slate-500">
        Built with React + Tailwind. © {new Date().getFullYear()} {RESUME.name}.
      </footer>

      {/* Floating Chatbot */}
      <Chatbot repos={repos} />
    </div>
  );
}