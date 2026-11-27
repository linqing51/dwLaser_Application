import type { Metadata } from 'next';
import './globals.css';
export const metadata: Metadata = {
  title: 'dwLaser S2 · Patient Case Demo',
  description: '激光设备 UI 与病历存储交互演示，无真实硬件连接。',
};
export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="zh-CN">
      <body>{children}</body>
    </html>
  );
}
